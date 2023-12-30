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

Position Box::getPos(std::chrono::time_point<std::chrono::high_resolution_clock> cutOffTime) const
{
    vector<BoxNote> boxNotes = getLastNotes(8);
    for(size_t ii=boxNotes.size()-1; ii >= 0; --ii)
    {
        BoxNote& boxNote = boxNotes[ii];
        if (4 == boxNote.getType())
        {
            std::chrono::duration<float> duration = cutOffTime - boxNote.getTimePoint();
            if (duration.count() >= 0)
            {
                return boxNote.getToPosition();
            }
        }
    }

    // cutOff not within the last 8 box notes, then check all the box notes.
    boxNotes = getAllNotes();

    for(size_t ii=boxNotes.size()-1; ii >= 0; --ii)
    {
        BoxNote& boxNote = boxNotes[ii];
        if (4 == boxNote.getType())
        {
            std::chrono::duration<float> duration = cutOffTime - boxNote.getTimePoint();
            if (duration.count() >= 0)
            {
                return boxNote.getToPosition();
            }
        }
    }

    // can not find an arrival in all of the notes.
    return Position{-1, -1};
}

void Box::addNote(BoxNote note)
{
    unique_lock lock(_mux);
    _notes.push_back(note);
}

vector<BoxNote> Box::getAllNotes() const
{
    shared_lock lock(_mux);
    return _notes; 
}

vector<BoxNote> Box::getLastNotes(int count) const
{
    shared_lock lock(_mux);
    auto start = next(_notes.begin(), (_notes.size()-count));
    vector<BoxNote> reduced(start, _notes.end());
    return reduced; 
}
        
