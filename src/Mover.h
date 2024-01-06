#ifndef MOVER__H
#define MOVER__H

#include "Position.h"

class Mover
{

public:

    virtual void addBox(Position position) = 0;

    virtual void moveBox(Position position) = 0;
};

#endif
