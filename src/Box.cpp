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

int Box::getX() const
{
    return 1;
}

int Box::getY() const
{
    return 1;
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

void Box::addNote(BoxNote note)
{
    _notes.push_back(note);
}

vector<BoxNote> Box::getAllNotes() const
{
   return _notes; 
}

vector<BoxNote> Box::getLastNotes(int count) const
{
    auto start = next(_notes.begin(), (_notes.size()-count));
    vector<BoxNote> reduced(start, _notes.end());
    return reduced; 
}
        
