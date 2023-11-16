#include "Board.h"

using namespace std;

Board::Board(int height, int width)
:   _height{height},
    _width{width}
{}

int Board::getHeight() const
{
    return _height;
}

int Board::getWidth() const
{
    return _width;
}

void Board::setHeight(int height)
{
    _height = height;
}

void Board::setWidth(int width)
{
    _width = width;
}

pair<int, int> Board::getLocation(int boxId) const
{
    return {_boxesPerId.at(boxId)->getX(), _boxesPerId.at(boxId)->getY()}; 
}

void Board::insert(int boxId, int height, int width, int xPos, int yPos)
{
    _boxesPerId.insert({boxId, make_unique<Box>(boxId, height, width, xPos, yPos)});
}  

void Board::move(int boxId, vector<Position> positions)
{
    _boxesPerId[boxId]->setX(positions[0].getX());
    _boxesPerId[boxId]->setY(positions[0].getY());
}
