#include "BoardNote.h"

BoardNote::BoardNote(int boxId, SpotType type):_type{type}, _boxId{boxId}
{}

bool BoardNote::operator== (const BoardNote& o) const
{
    return _type == o._type && _boxId == o._boxId;
}

SpotType BoardNote::getType() const
{
    return _type;
}

int BoardNote::getBoxId() const
{
    return _boxId;
}
