#ifndef MOVER__H
#define MOVER__H

#include "Position.h"

/*
Adds Boxes to a Board.
Removes Boxes from a Board.
Moves Boxes on the Board.
*/

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

    /*
    Adds a Box to the Board at @position. If this addition is unsuccessful, neither Boxes' levels go up.
    */
    virtual bool addBox(Position position) = 0;

    virtual bool removeBox(Position position) = 0;

    /*
    Moves a Box on the Board from @oldPosition to @newPosition. If the move is unsuccessful, both Boxes' levels to up by one.
    */
    virtual bool moveBox(Position oldPosition, Position newPosition) = 0;

    virtual int getBoxId() const = 0;
};

#endif
