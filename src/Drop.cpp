#include "Drop.h"

Drop::Drop(int x, int y):_position{x, y}{};

Drop::Drop(
    int x,
    int y,
    int boxId,
    MoveType type)
:   _position{x, y},
    _boxId{boxId},
    _type{type}
{}


void Drop::setBoxId(int id)
{
    _boxId = id;
}

void Drop::setMoveType(MoveType type)
{
    _type = type;
}

void Drop::setHasChanged(bool hasChanged)
{
    _changed = hasChanged;
}

Position Drop::getPosition() const
{
    return _position;
}

int Drop::getBoxId() const
{
    return _boxId;
}

MoveType Drop::getMoveType() const
{
    return _type;
}

bool Drop::hasChanged() const
{
    return _changed;
}

bool Drop::operator==(const Drop& o) const
{
    return _position.getX() == o._position.getX() && _position.getY() == o._position.getY();
}
