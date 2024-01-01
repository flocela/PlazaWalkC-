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
        if (note.getType() == 3)
        {
            _notes.erase(note.getBoxId());
        }
        else
        {
            _notes.erase(note.getBoxId());
            _notes.insert({note.getBoxId(), note});
        }
    }
}
