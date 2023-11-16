#include "Position.h"

Position::Position(int x, int y)
: _x{x}, _y{y}
{}

int Position::getX()
{
    return _x;
}

int Position::getY()
{
    return _y;
}
