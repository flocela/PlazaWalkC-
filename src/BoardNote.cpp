#include "BoardNote.h"

BoardNote::BoardNote(int type, int boxId):_type{type}, _boxId{boxId}
{}

int BoardNote::getType() const
{
    return _type;
}

int BoardNote::getBoxId() const
{
    return _boxId;
}
