#include "Board.h"

using namespace std;

Board::Board(int width, int height)
:   _width{width},
    _height{height}
{
    for(int row=0; row<height; ++row)
    {
        vector<Spot> rowOfSpots{};
        for(int col=0; col<width; ++col)
        {
            rowOfSpots.push_back(Spot(Position(row, col)));
        }
        _spots.push_back(rowOfSpots);
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

bool Board::addNote(Position position, BoardNote boardNote)
{
    bool success = _spots[position.getY()][position.getX()].tagNote(boardNote);

    if (_boardCallbacksPerPos.find(position) != _boardCallbacksPerPos.end())
    {
        _boardCallbacksPerPos.at(position).callback(position);
    }
    // TODO BoardCallback& should be const
    for (BoardCallback* callback : _boardCallbacks)
    {
        callback->callback(position);
    }

    return success;
}

BoardNote Board::getNoteAt(Position position) const
{
    return BoardNote{_spots[position.getY()][position.getX()].getBoxId(),
                     _spots[position.getY()][position.getX()].getType()};
}

void Board::registerCallback(Position pos, BoardCallback& callBack)
{
    _boardCallbacksPerPos.insert({pos, callBack});
}

void Board::registerCallback(BoardCallback* callBack)
{
    _boardCallbacks.insert(callBack);
}
