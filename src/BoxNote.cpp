#include "BoxNote.h"

using namespace std;

BoxNote::BoxNote(int type, Position toPosition, Position fromPosition, std::chrono::time_point<std::chrono::high_resolution_clock> timeStamp
):  _type{type}, _toPosition{toPosition}, _fromPosition{fromPosition}, _timeStamp{timeStamp}
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

std::chrono::time_point<std::chrono::high_resolution_clock> BoxNote::getTimePoint() const
{
    return _timeStamp;
}

bool BoxNote::operator== (const BoxNote& o) const
{
    return  _type == o._type &&
            _toPosition == o._toPosition && 
            _fromPosition == o._fromPosition &&
            _timeStamp == o._timeStamp;
}
