#ifndef MOVER__H
#define MOVER__H

#include "Position.h"

// Adds Boxes to a Board.
// Removes Boxes from a Board.
// Moves Boxes on Board.
class Mover
{

protected:
    Mover() = default;
    Mover(const Mover& o) = default;
    Mover(Mover&& o) noexcept = default;
    Mover& operator=(const Mover& o) = default;
    Mover& operator=(Mover&& o) noexcept = default;

public:

    virtual ~Mover () noexcept = default;
    virtual bool addBox(Position position) = 0;
    virtual bool removeBox(Position position) = 0;
    virtual bool moveBox(Position oldPosition, Position newPosition) = 0;
    virtual int getBoxId() const = 0;
};

#endif
