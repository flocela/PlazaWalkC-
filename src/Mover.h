#ifndef MOVER__H
#define MOVER__H

#include "Position.h"

class Mover
{

public:

    virtual bool addBox(Position position) = 0;

    virtual bool moveBox(Position oldPosition, Position newPosition) = 0;
};

#endif
