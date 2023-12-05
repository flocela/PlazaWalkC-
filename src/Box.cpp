#include "Box.h"

using namespace std;

Box::Box (int id, int height, int width, int xPos, int yPos)
:   _id{id},
    _height{height},
    _width{width},
    _xPos{xPos},
    _yPos{yPos}
    
{}
// TODO need a test for == operator that makes sure that each attribute is in the return statement list.
bool Box::operator== (const Box& o) const
{
    return  _id == o._id &&
            _height == o._height &&
            _width == o._width &&
            _xPos  == o._xPos &&
            _yPos  == o._yPos;
}

int Box::getId() const
{
    return _id;
}

int Box::getX() const
{
    return _xPos;
}

int Box::getY() const
{
    return _yPos;
}

void Box::setX(int xPos)
{   
    _xPos = xPos;
}

void Box::setY(int yPos)
{   
    _yPos = yPos;
}

int Box::getHeight() const
{
    return _height;
}

int Box::getWidth() const
{
    return _width;
}

void Box::setHeight(int height)
{
    _height = height;
}

void Box::setWidth(int width)
{
    _width = width;
}
