#include "Board.h"

using namespace std;

Board::Board(int height, int width, vector<Box*> boxes)
:   _height{height},
    _width{width},
    _boxes{boxes}
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

