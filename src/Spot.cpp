#include "Spot.h"

using namespace std;

Spot::Spot(Position pos):_position{pos}
{}

Position Spot::getPosition() const
{
    return _position;
}

unordered_map<int, BoardNote> Spot::getNotes() const
{
    return _notes;
}

void Spot::tagNote(BoardNote note)
{
    unordered_map<int, BoardNote>::iterator it = _notes.find(note.getBoxId());
    if (it == _notes.end())
    {
        _notes.insert({note.getBoxId(), note});
    }
    else
    {   
        // If note is type 3, box has left. Erase existing box note from map because spot no 
        // longer needs to keep track of this box.
        if (note.getType() == 3)
        {
            _notes.erase(note.getBoxId());
        }
        else
        {
            _notes.at(note.getBoxId()) = note;
        }
    }
}
