#include "Box.h"

using namespace std;

Box::Box (int id, int width, int height)
:   _id{id},
    _width{width},
    _height{height}
{}

Box::Box(const Box& o): _id{o._id}, _level{o._level}, _width{o._width}, _height{o._height}
{}

Box::Box(Box&& o) noexcept: _id{o._id}, _level{o._level}, _width{o._width}, _height{o._height}
{}


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

int Box::getLevel() const
{
    shared_lock<shared_mutex> lock(_mm);
    return _level;
}

void Box::upLevel()
{
    unique_lock<shared_mutex> lock(_mm);
    ++_level;
}
    
