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

// TODO what do I do if I get a type 2 before I get a type 1?
void Spot::tagNote(BoardNote note)
{
    unordered_map<int, BoardNote>::iterator it = _notes.find(note.getBoxId());
    if (it == _notes.end())
    {
        _notes.insert({note.getBoxId(), note});
    }
    else
    {
        _notes.erase(note.getBoxId());
    }
}
