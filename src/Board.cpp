#include "Board.h"
#include "BoardListener.h"

using namespace std;

Board::Board(
    int width,
    int height,
    vector<Box>&& boxes)
:   _width{width},
    _height{height}
{
    // _spots contains height x width number of Spots.
    // _dropMatrix1 and _dropMatrix2 contain height x width number of Drops.
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

    // set _receivingMatrix to one of the Drop matrices.
    _receivingMatrix = &_dropMatrix1;

    // Move the Boxes from boxes to _boxes.
    for(const Box& box : boxes)
    {  
        _boxes.emplace(pair<int, Box>{box.getId(), std::move(box)});
    }
}

/*
Spots, Drops, and Boxes are only updated in the addNote() method. These updates are stopped while collecting the data to send in the sendStateAndChanges() method. The addNote() method is protected by a shared_lock using the mutex _mux.

The toggling of _receivingMatrix and the copying of _boxes sendStateAndChanges() is protected by a unique_lock.  This unique_lock shares the same mutex (_mux) as the shared_lock that protects all of addNote().

Note, addNote() allows multiple threads to use it at the same time.


A particular Spot and its corresponding Drop in _recevingMatrix should be changing in unison. Spot's changes are protected with locks inside Spot's methods. Drop doesn't have any protections. However, threads (through their contained PositionManager) contain a particular boxId. Once a thread has successfully changed a Spot with the "to arrive" type and a particular boxId, the Spot is essentially stamped with that particular boxId. Only that particular thread can change that Spot because only that particular thread has that boxId. At that point only that particular thread changes the corresponding Drop's attributes. Not until that particular thread changes the Spot's type to "left" and finishes the addNote() method can another thread change that particular Spot or its corresponding Drop.
*/
bool Board::addNote(Position position, BoardNote newNote)
{
    shared_lock<shared_mutex> shLock(_mux);

    // Only allow Boxes that are in the _boxes vector to be added to the Board.
    if(_boxes.find(newNote.getBoxId()) == _boxes.end())
    {
        string str = "Trying to add a BoardNote with a boxId of ";
        str.append(to_string(newNote.getBoxId()));
        str.append(" when there is no Box with that boxId.");
        throw(invalid_argument(str));
    }

    // See Spot class' rules that determine if a Box with this boxId and SpotType at @position is allowed. Put basically, @position has to be empty in order for a Box to enter the Spot. And only a BoardNote with the Spot's current boxId can move the Box out of the Spot.
    pair<int, bool> success = _spots[position.getY()][position.getX()].changeNote(newNote);
    
    if (success.second)
    {
        // Record changed boxId and type at @position in _receivingMatrix.
        BoardNote currentBoardNote = _spots[position.getY()][position.getX()].getBoardNote();
        Drop& drop = (*_receivingMatrix)[position.getY()][position.getX()];
        drop.setHasChanged(true);
        drop.setBoxId(currentBoardNote.getBoxId());

        // In order to fail a test, Add a sleep time here.
        // std::this_thread::sleep_for(1ms);

        drop.setSpotType(currentBoardNote.getType());

        // Move was successful. Notify all NoteSubscribers.
        if (_noteSubscribersPerPos.find(position) != _noteSubscribersPerPos.end())
        {
            _noteSubscribersPerPos.at(position).callback(newNote);
        }

        return true;
    }
    else
    {
        // Movement was not successful. Both boxes' levels are increased by one.
        _boxes[success.first].upLevel();
        _boxes[newNote.getBoxId()].upLevel();

        return false; 
    }
}

void Board::sendStateAndChanges()
{   
    // The sendChangesLock prevents two threads entering sendChanges() method at the same time.
    unique_lock<shared_mutex> sendChangesLock(_sendChangesMutex);

    // changedBoard will point to the current _receivingMatrix.
    vector<vector<Drop>>* changedBoard = nullptr;
    unordered_map<int, BoxInfo> copyOfBoxInfo{};
    {
        // While 1) toggling _receivedMatrix, 2) assigning changedBoard, and 3) copying _boxes boxInfos, no new notes are being added. addNote() shares the _mux mutex that lockUq is using.
        unique_lock<shared_mutex> lockUq(_mux);
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
Note changes to a Spot (via addNote()) can happen at the same time that getNoteAt() is being called.
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
