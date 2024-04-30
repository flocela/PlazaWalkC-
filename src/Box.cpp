#include "Box.h"
#include <iostream>
using namespace std;

Box::Box (
    int id,
    int group,
    int width,
    int height)
:   _id{id},
    _groupid{group},
    _width{width},
    _height{height}
{}

Box::Box(const Box& o)
:   _id{o._id},
    _groupid{o._groupid},
    _level{o._level},
    _width{o._width},
    _height{o._height}
{}

Box::Box(Box&& o) noexcept
:   _id{o._id},
    _groupid{o._groupid},
    _level{o._level},
    _width{o._width},
    _height{o._height}
{}
    
bool Box::operator== (const Box& o) const
{
    return  _id == o._id &&
            _width == o._width &&
            _height == o._height &&
            _groupid == o._groupid;
}

int Box::getId() const
{
    return _id;
}

int Box::getGroupId() const
{
    return _groupid;
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

BoxInfo Box::getInfo() const
{
    shared_lock<shared_mutex> lock(_mm);
    return BoxInfo{_id, _groupid, _width, _height, _level};
}
