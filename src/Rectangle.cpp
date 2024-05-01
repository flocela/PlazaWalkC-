#include "Rectangle.h"

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

bool Rectangle::operator== (const Rectangle& o) const
{
    return _topLeft == o._topLeft &&
           _bottomRight == o._bottomRight;
} 
