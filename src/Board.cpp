#include "Board.h"

using namespace std;

Board::Board(
    int width,
    int height,
    vector<Box>&& boxes)
:   _width{width},
    _height{height}
{
    // The number of Spots that _spots contains is height times width.
    // The number of Drops that both _dropMatrix1 and _dropMatrix2 contain is height x width.
    _spots = vector<vector<Spot>>(height,vector<Spot>{});
    _dropMatrix1 = vector<vector<Drop>>(height, vector<Drop>{});
    _dropMatrix2 = vector<vector<Drop>>(height, vector<Drop>{});

    for(int row=0; row<height; ++row)
    {
        for(int col=0; col<width; ++col)
        {
            _spots[row].push_back(Spot{Position{col, row}});
            _dropMatrix1[row].push_back(Drop{col, row});
            _dropMatrix2[row].push_back(Drop{col, row});
        }
    }

    // Set _receivingMatrix to one of the Drop matrices.
    _receivingMatrix = &_dropMatrix1;

    // Move the Boxes from boxes to _boxes.
    for(const Box& box : boxes)
    {  
        _boxes.emplace(pair<int, Box>{box.getId(), std::move(box)});
    }
}

/*
Spots, Drops, and Boxes are only updated in the changeSpot() method. These updates are paused while the data collection is done in the sendStateAndChanges() method. The changeSpot() method is protected by a shared_lock using the mutex _mux. The data collection is uniquely and entirely done in the the sendStateAndChanges() method, and the task for collecting that data is surrounded by a unique_lock that also uses the _mux mutex. The task for collecting that data is the toggling of the _receivingMatrix and the copying of _boxes.

Note, changeSpot() allows multiple threads to use it at the same time; It is protected by a shard_lock.

A particular Spot and its corresponding Drop in _recevingMatrix should be changing in unison. Spot's changes are protected with locks inside Spot's methods. Drop doesn't have any protections. However, threads (through their contained Mover) contain a particular boxId. Once a thread has successfully changed a Spot with the "to arrive" type and a particular boxId, the Spot is essentially stamped with that particular boxId. Only that particular thread can change that Spot because only that particular thread has that boxId. At that point only that particular thread changes the corresponding Drop's attributes. Not until that particular thread changes the Spot's type to "left" and finishes the changeSpot() method can another thread change that particular Spot or its corresponding Drop.
*/
bool Board::changeSpot(Position position, BoardNote newNote, bool upLevel)
{
    shared_lock<shared_mutex> shLock(_mux);

    int posX = position.getX();
    int posY = position.getY();

    // Only allow Boxes that are in the _boxes vector to be added to the Board.
    if(_boxes.find(newNote.getBoxId()) == _boxes.end())
    {
        string str = "Trying to add a BoardNote with a boxId of ";
        str.append(to_string(newNote.getBoxId()));
        str.append(" when there is no Box with that boxId.");
        throw(invalid_argument(str));
    }

    // Try to update Spot at @position.
    // See Spot class' rules to determine if a Box with this boxId and SpotType at @position is allowed. Hint: Put basically, @position has to be empty in order for a Box to enter the Spot. And only a BoardNote with the Spot's current boxId can move the Box out of the Spot.
    pair<int, bool> success = _spots[posY][posX].changeNote(newNote);
    
    if (success.second)
    {
        // Record changes to Spot in _receivedMatrix, which is a matrix of Drops.
        BoardNote changedBoardNote = _spots[posY][posX].getBoardNote();
        Drop& drop = (*_receivingMatrix)[posY][posX];

        // Record that this Drop has changed.
        drop.setHasChanged(true);

        // Record changed boxId.
        drop.setBoxId(changedBoardNote.getBoxId());

        // In order to fail a threading test, Add a sleep time here.
        // std::this_thread::sleep_for(1ms);

        // Record changed SpotType.
        drop.setSpotType(changedBoardNote.getType());

        // Move was successful. Notify all NoteSubscribers.
        if (_noteSubscribersPerPos.find(position) != _noteSubscribersPerPos.end())
        {
            _noteSubscribersPerPos.at(position).callback(newNote);
        }

        return true;
    }
    else
    {
        if(upLevel)
        {
            // Movement was not successful. Both boxes' levels are increased by one.
            _boxes[success.first].upLevel();
            _boxes[newNote.getBoxId()].upLevel();
        }
        return false; 
    }
}

void Board::sendStateAndChanges()
{   
    // The uniqueLock, enteringMethodLock, prevents two threads entering the sendStateAndChanges() method at the same time. No other method uses the _enteringMethodMutex.
    unique_lock<shared_mutex> enteringMethodLock(_enteringMethodMutex);


    // changedBoard will point to the current _receivingMatrix.
    vector<vector<Drop>>* changedBoard = nullptr;
    unordered_map<int, BoxInfo> copyOfBoxInfo{};

    // Braces encapsulate the task of data collection. The data does not change during this task. While 1) toggling _receivedMatrix, 2) assigning changedBoard, and 3) copying _boxes' boxInfos, no new notes are being added due to changeSpot() sharing the _mux mutex that collectDataLock is using.
    {
        unique_lock<shared_mutex> collectDataLock(_mux);
        
        changedBoard = _receivingMatrix;
        _receivingMatrix = (_receivingMatrix == &_dropMatrix1) ? (&_dropMatrix2) : (&_dropMatrix1);
        
        // Copy BoxInfos to send.
        for(const auto& p : _boxes)
        {
            copyOfBoxInfo.insert({p.first, p.second.getInfo()});
        }
    }

    // Collect changed Drops from changedBoard.
    unordered_set<Drop> changedDrops;

    for (int row=0; row<_height; ++row)
    {
        for (int col=0; col<_width; ++col)
        {
            Drop curDrop = (*changedBoard)[row][col];
            if (curDrop.hasChanged())
            {
                changedDrops.insert(curDrop);
                (*changedBoard)[row][col].setBoxId(-1);
                (*changedBoard)[row][col].setSpotType(SpotType::left);
                (*changedBoard)[row][col].setHasChanged(false);
            }
        }
    }

    // Send changes to Drops and set of BoxInfo to BoardListeners.
    for(BoardListener* listener : _listeners)
    {
        listener->receiveChanges(changedDrops, copyOfBoxInfo);
    }
}

/*
Note changes to a Spot (via changeSpot()) can happen at the same time that getNoteAt() is being called.
*/
BoardNote Board::getNoteAt(Position position) const
{
    shared_lock<shared_mutex> lock(_mux);
    return _spots[position.getY()][position.getX()].getBoardNote();
}

void Board::registerListener(BoardListener* listener)
{
    _listeners.insert(listener);
}


int Board::getWidth() const
{
    return _width;
}

int Board::getHeight() const
{
    return _height;
}

void Board::registerNoteSubscriber(Position pos, NoteSubscriber& subscriber)
{
    _noteSubscribersPerPos.insert({pos, subscriber});
}

BoardProxy Board::getBoardProxy()
{
    return BoardProxy(*this);
}
