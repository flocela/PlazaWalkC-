#include "Box.h"

using namespace std;

Box::Box (int id, int width, int height)
:   _id{id},
    _width{width},
    _height{height}
{}
// TODO need a test for == operator that makes sure that each attribute is in the return statement list.
bool Box::operator== (const Box& o) const
{
    return  _id == o._id &&
            _width == o._width &&
            _height == o._height;
}

int Box::getId() const
{
    return _id;
}

int Box::getHeight() const
{
    return _height;
}

int Box::getWidth() const
{
    return _width;
}

Position Box::getPosition() const
{ 
    return _position;
}

void Box::setPosition(Position position)
{
    _position = position;
};

