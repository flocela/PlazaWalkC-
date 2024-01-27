#include "BoardNote.h"

BoardNote::BoardNote(int boxId, int type):_type{type}, _boxId{boxId}
{}

// Needs a test for operator==
bool BoardNote::operator== (const BoardNote& o) const
{
    return _type == o._type && _boxId == o._boxId;
}

int BoardNote::getType() const
{
    return _type;
}

int BoardNote::getBoxId() const
{
    return _boxId;
}
