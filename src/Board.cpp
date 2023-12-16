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

void Board::addNote(Position position, BoardNote boardNote)
{
    _spots[position.getY()][position.getX()].tagNote(boardNote);
}

unordered_map<int, BoardNote> Board::getNotes(Position position) const
{
    return _spots[position.getY()][position.getX()].getNotes();
}
