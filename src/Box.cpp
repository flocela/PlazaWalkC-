#include "Box.h"
#include <iostream>
using namespace std;

Box::Box (int id, int group, int width, int height)
:   _id{id},
    _groupid{group},
    _width{width},
    _height{height}
{}

Box::Box(const Box& o): _id{o._id}, _groupid{o._groupid}, _level{o._level}, _width{o._width}, _height{o._height}
{}

Box::Box(Box&& o) noexcept: _id{o._id}, _groupid{o._groupid}, _level{o._level}, _width{o._width}, _height{o._height}
{}

// TODO is this tested?
void Box::setId(int id)
{
    unique_lock<shared_mutex> lock(_mm);
    if (_id != -1)
    {
        string str = "Trying to assign id of ";
        str.append(to_string(id));
        str.append(" to Box with an existing _id of ");
        str.append(to_string(_id));
        str.append(".");
        throw invalid_argument(str);
    }
    _id = id;
}

// TODO is this tested?
// TODO probably shouldn't be using same mutex???
void Box::setGroupid(int groupid)
{
    unique_lock<shared_mutex> lock(_mm);
    if(_groupid != -1)
    {
        string str = "Trying to assign groupid of ";
        str.append(to_string(groupid));
        str.append(" to Box with an existing _groupid of ");
        str.append(to_string(_groupid));
        str.append(".");
        throw invalid_argument(str);
    }
    _groupid = groupid;
}
        
    
void Box::setWidth(int w)
{
    unique_lock<shared_mutex> lock(_mm);
    if (_width != -1)
    {
        string str = "Trying to assign width of ";
        str.append(to_string(w));
        str.append(" to Box with an existing _width of ");
        str.append(to_string(_width));
        str.append(".");
        throw invalid_argument(str);
    }
    _width = w;
    
}

void Box::setHeight(int h)
{
    unique_lock<shared_mutex> lock(_mm);
    if (_height!= -1)
    {
        string str = "Trying to assign height of ";
        str.append(to_string(h));
        str.append(" to Box with an existing _height of ");
        str.append(to_string(_height));
        str.append(".");
        throw invalid_argument(str);
    }
    _height = h;
}

bool Box::operator== (const Box& o) const
{
    return  _id == o._id &&
            _width == o._width &&
            _height == o._height;
}

int Box::getId() const
{
    shared_lock<shared_mutex> lock(_mm);
    return _id;
}

int Box::getGroupId() const
{
    shared_lock<shared_mutex> lock(_mm);
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
    
