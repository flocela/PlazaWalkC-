#include "Position.h"

#include <iostream>

using namespace std;


Position::Position(int x, int y)
: _x{x}, _y{y}
{}

int Position::getX() const
{
    return _x;
}

int Position::getY() const
{
    return _y;
}

bool Position::operator== (const Position& o) const
{  
    return _x == o._x && _y == o._y;
}

std::string Position::toString() const
{
    string str{"["};
    str.append(to_string(_x));
    str.append(", ");
    str.append(to_string(_y));
    str.append("]");
    return str;
}
