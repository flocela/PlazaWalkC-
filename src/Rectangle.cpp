#include "Rectangle.h"

#include <sstream>

using namespace std;

Rectangle::Rectangle(Position a, Position b)
:   _topLeft{Position{std::min(a.getX(), b.getX()), std::min(a.getY(), b.getY())}},
    _bottomRight{Position{std::max(a.getX(), b.getX()), std::max(a.getY(), b.getY())}}
{}

Position Rectangle::getTopLeft() const
{
    return _topLeft;
}

Position Rectangle::getBottomRight() const
{
    return _bottomRight;
}

string Rectangle::toString() const
{
    stringstream ss;
    ss << (*this);
    return ss.str(); 
}

Position Rectangle::getCenter() const
{
    return Position{_topLeft.getX() + ((_bottomRight.getX() - _topLeft.getX())/2),
                    _topLeft.getY() + ((_bottomRight.getY() - _topLeft.getY())/2)};
}

bool Rectangle::isInside(Position p) const
{
    return p.getX() >= _topLeft.getX() && p.getX() <= _bottomRight.getX() &&
           p.getY() >= _topLeft.getY() && p.getY() <= _bottomRight.getY();
}

bool Rectangle::operator== (const Rectangle& o) const
{
    return _topLeft == o._topLeft &&
           _bottomRight == o._bottomRight;
} 
