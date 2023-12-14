#include "BoxNote.h"

using namespace std;

BoxNote::BoxNote(int type, Position toPosition, Position fromPosition
):  _type{type}, _toPosition{toPosition}, _fromPosition{fromPosition}
{}

int BoxNote::getType() const
{
    return _type;
}

Position BoxNote::getToPosition() const
{
    return _toPosition;
}

Position BoxNote::getFromPosition() const
{
    return _fromPosition;
}
