#include "BoxTaken.h"

using namespace std;

BoxTaken::BoxTaken(const BoxTaken& o): _state{o._state}
{}

BoxTaken::BoxTaken(BoxTaken&& o) noexcept: _state{o._state}
{}

void BoxTaken::changeToTrue()
{
    unique_lock<shared_mutex> lock(_mm);
    _state = true;
}

bool BoxTaken::getState() const
{
    shared_lock<shared_mutex> lock(_mm);
    return _state;
}
