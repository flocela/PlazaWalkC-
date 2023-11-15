#include "Box.h"

Box::Box (int height, int width, int xPos, int yPos)
:   _height{height},
    _width{width},
    _xPos{xPos},
    _yPos{yPos}
    
{}

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
