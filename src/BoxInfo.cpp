#include "BoxInfo.h"

using namespace std;

BoxInfo::BoxInfo (int id, int group, int width, int height, int level)
:   _id{id},
    _groupid{group},
    _width{width},
    _height{height},
    _level{level}
{}

bool BoxInfo::operator== (const BoxInfo& o) const
{
    return  _id == o._id &&
            _groupid == o._groupid && 
            _width == o._width &&
            _height == o._height &&
            _level == o._level;
}

int BoxInfo::getId() const
{
    return _id;
}

int BoxInfo::getGroupId() const
{
    return _groupid;
}

int BoxInfo::getHeight() const
{
    return _height;
}

int BoxInfo::getWidth() const
{
    return _width;
}

int BoxInfo::getLevel() const
{
    return _level;
}
    
