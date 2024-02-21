#ifndef MOVER__H
#define MOVER__H

#include "Position.h"

class Mover
{

protected:
    Mover() = default;
    Mover(const Mover& o) = default;
    Mover(Mover&& o) noexcept = default;
    Mover& operator=(const Mover& o) = default;
    Mover& operator=(Mover&& o) noexcept = default;

public:

    virtual bool addBox(Position position) = 0;
    virtual bool moveBox(Position oldPosition, Position newPosition) = 0;
    virtual ~Mover () noexcept = default;
};

#endif
