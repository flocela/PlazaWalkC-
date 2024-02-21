#include "Board.h"
#include "BoardListener.h"

using namespace std;

Board::Board(int width, int height)
:   _width{width},
    _height{height}
{
    for(int row=0; row<height; ++row)
    {
        vector<Spot> rowOfSpots{};
        vector<Drop> rowOfDrops1{};
        vector<Drop> rowOfDrops2{};
        for(int col=0; col<width; ++col)
        {
            rowOfSpots.push_back(Spot{Position{col, row}});
            rowOfDrops1.push_back(Drop{col, row});
            rowOfDrops2.push_back(Drop{col, row});
        }
        _spots.push_back(rowOfSpots);
        _dropBoard1.push_back(rowOfDrops1);
        _dropBoard2.push_back(rowOfDrops2);
    }
    _curDropBoard = &_dropBoard1;
}

int Board::getWidth() const
{
    return _width;
}

int Board::getHeight() const
{
    return _height;
}

bool Board::addNote(Position position, BoardNote boardNote)
{
    shared_lock<shared_mutex> lockShared(_mux);

    bool success = _spots[position.getY()][position.getX()].tagNote(boardNote);
   
    if (success)
    {
        // Record change in boxId and/or type at position in _curDropBoard.

        (*_curDropBoard)[position.getY()][position.getX()]._boxId = _spots[position.getY()][position.getX()].getBoxId();
        (*_curDropBoard)[position.getY()][position.getX()]._type = _spots[position.getY()][position.getX()].getType();
        (*_curDropBoard)[position.getY()][position.getX()]._changed = true;

        // Notify all BoardCallbacks. Should be zero as BoardCallbacks are only used in testing.
        if (_boardCallbacksPerPos.find(position) != _boardCallbacksPerPos.end())
        {
            _boardCallbacksPerPos.at(position).callback(boardNote, position);
        }
    }

    return success;
}

void Board::registerCallback(Position pos, BoardCallback& callBack)
{
    _boardCallbacksPerPos.insert({pos, callBack});
}

// TODO sendChanges() should only be called by one thread at a time.
void Board::sendChanges()
{
    // changedBoard holds the current matrix where changes are being made. 
    vector<vector<Drop>>* changedBoard = _curDropBoard;

    // Toggle _curDropBoard to _dropBoard1 or dropBoard2.
    // New changes from addNote() will be recorded in the newly selected board while changes are made to changedBoard.
    {
        unique_lock<shared_mutex> lockUq(_mux);    
        _curDropBoard = (_curDropBoard == &_dropBoard1) ? (&_dropBoard2) : (&_dropBoard1);
    }
  
    // TODO return setOfDropsPerPosition changing to per type should be done by the listener
    // Collect changes in setsOfDropsPerType  
    unordered_map<int, unordered_set<Drop>> setsOfDropsPerType;

    for (int row=0; row<_height; ++row)
    {
        for (int col=0; col<_width; ++col)
        {
            Drop curDrop = (*changedBoard)[row][col];
            if (curDrop._changed)
            {
                setsOfDropsPerType[curDrop._type].insert(curDrop);
                (*changedBoard)[row][col]._boxId = -1;
                (*changedBoard)[row][col]._type = -1;
                (*changedBoard)[row][col]._changed = false;
            }
        }
    }
    
    for(BoardListener* listener : _listeners)
    {   
        listener->receiveChanges(setsOfDropsPerType);
    }
}

void Board::registerListener(BoardListener* listener)
{
    _listeners.insert(listener);
}

// TODO check that this shouldn't be locked.
BoardNote Board::getNoteAt(Position position) const
{
    unique_lock<shared_mutex> lock(_mux);
    return BoardNote{_spots[position.getY()][position.getX()].getBoxId(),
                     _spots[position.getY()][position.getX()].getType()};
}
