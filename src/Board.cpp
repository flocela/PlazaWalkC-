#include "Board.h"
#include "BoardListener.h"
#include <thread>
#include <chrono>

using namespace std;

Board::Board(
    int width,
    int height,
    vector<Box>&& boxes)
:   _width{width},
    _height{height}
{
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

    _receivingMatrix = &_dropMatrix1;

    for(const Box& box : boxes)
    {  
        _boxes.emplace(pair<int, Box>{box.getId(), std::move(box)});
    }
}

int Board::getWidth() const
{
    return _width;
}

int Board::getHeight() const
{
    return _height;
}

// Many threads can be inside addNote() at the same time, it is protected by a shared_lock.
// Although many threads can be inside addNote() at the same time, only one thread can change a particular spot at one time. Spot's changeNote() method is protected by a unique_lock.

// The shared_lock protecting addNote() will not allow changes to any Spot or any Drop while the _receivingMatrix is being toggled.

// A particular Spot and its corresponding Drop in _recevingMatrix should be changing in unison. Spot's changes are protected with locks inside Spot's methods. Drop doesn't have any protections. However, threads (through their contained PositionManager) contain a particular boxId. Once a thread has successfully changed a Spot with the "to arrive" type and a particular boxId, the Spot is essentially stamped with that particular boxId. Only that particular thread can change that Spot because only that particular thread has that boxId. At that point only that particular thread changes the corresponding Drop's attributes. Not until that particular thread changes the Spot's type to "left" and finishes the addNote() method can another thread change that particular Spot or its corresponding Drop.
bool Board::addNote(Position position, BoardNote newNote)
{
    shared_lock<shared_mutex> shLock(_mux);

    // Can not put Box on the Board (change Spot) if Box is not in Board's map of Boxes.
    if(_boxes.find(newNote.getBoxId()) == _boxes.end())
    {
        string str = "Trying to add a BoardNote with a boxId of ";
        str.append(to_string(newNote.getBoxId()));
        str.append(" when there is no Box with that boxId.");
        throw(invalid_argument(str));
    }

    // See Spot's rules that determine if Box's movement at Position is allowed. But basically, Position has to either be empty, or already be occupied by this Box in order for movement to be successful.
    pair<int, bool> success = _spots[position.getY()][position.getX()].changeNote(newNote);
    
    if (success.second)
    {
        // Record changed boxId and type at position in _receivingMatrix.
        BoardNote currentBoardNote = _spots[position.getY()][position.getX()].getBoardNote();
        Drop& drop = (*_receivingMatrix)[position.getY()][position.getX()];
        drop._changed = true;
        drop._boxId = currentBoardNote.getBoxId();
        // In order to fail a test, Add a sleep time here.
        // std::this_thread::sleep_for(1ms);
        drop._type = currentBoardNote.getType();

        // Notify all NoteSubscriber.
        if (_noteSubscribersPerPos.find(position) != _noteSubscribersPerPos.end())
        {
            _noteSubscribersPerPos.at(position).callback(newNote, position);
        }

        return true;
    }
    else
    {
        // Movement was not successful
        _boxes[success.first].upLevel();
        _boxes[newNote.getBoxId()].upLevel();

        return false; 
    }
}

void Board::registerNoteSubscriber(Position pos, NoteSubscriber& subscriber)
{
    _noteSubscribersPerPos.insert({pos, subscriber});
}

void Board::sendChanges()
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
        
        // copy BoxInfos to send 
        for(const auto& p : _boxes)
        {
            copyOfBoxInfo.insert({p.first, p.second.getInfo()});
        }
    }

    // Collect changes in setsOfDropsPerType  
    unordered_map<SpotType, unordered_set<Drop>> setsOfDropsPerType;

    for (int row=0; row<_height; ++row)
    {
        for (int col=0; col<_width; ++col)
        {
            Drop curDrop = (*changedBoard)[row][col];
            if (curDrop._changed)
            {
                setsOfDropsPerType[curDrop._type].insert(curDrop);
                (*changedBoard)[row][col]._boxId = -1;
                (*changedBoard)[row][col]._type = SpotType::left;
                (*changedBoard)[row][col]._changed = false;
            }
        }
    }

    // Send changes to Drops and set of BoxInfo to BoardListeners.
    for(BoardListener* listener : _listeners)
    {
        listener->receiveChanges(setsOfDropsPerType, copyOfBoxInfo);
    }
}

void Board::registerListener(BoardListener* listener)
{
    _listeners.insert(listener);
}

// Note changes to a Spot (via addNote()) can happen at the same time that getNoteAt() is being called.
BoardNote Board::getNoteAt(Position position) const
{
    shared_lock<shared_mutex> lock(_mux);
    return _spots[position.getY()][position.getX()].getBoardNote();
}

