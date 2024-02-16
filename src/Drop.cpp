#include "Drop.h"

Drop::Drop(int x, int y):_position{x, y}{};

bool Drop::operator==(const Drop& o) const
{
    return _position.getX() == o._position.getX() && _position.getY() == o._position.getY();
}
