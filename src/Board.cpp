#include "Board.h"

using namespace std;

Board::Board(int height, int width)
:   _height{height},
    _width{width},
    _boxIdsOnBoard(height, vector<int>(width, -1))
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

Position Board::getLocation(int boxId) const
{
    return Position{_boxesPerId.at(boxId)->getX(), _boxesPerId.at(boxId)->getY()}; 
}

// TODO this may insert a box on top of another box.
void Board::insert(int boxId, int height, int width, int xPos, int yPos)
{
    _boxesPerId.insert({boxId, make_unique<Box>(boxId, height, width, xPos, yPos)});
    _boxIdsOnBoard[yPos][xPos] = boxId;
}  

void Board::move(int boxId, vector<Position> positions)
{
    for (Position& pos : positions)
    {
        if (_boxIdsOnBoard[pos.getY()][pos.getX()] == -1)
        {   
            _boxIdsOnBoard[_boxesPerId[boxId]->getY()][_boxesPerId[boxId]->getX()] = -1;   
            _boxesPerId[boxId]->setX(pos.getX());
            _boxesPerId[boxId]->setY(pos.getY());
            _boxIdsOnBoard[pos.getY()][pos.getX()] = boxId;
            break;
        }
    }
}
