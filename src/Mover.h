#ifndef MOVER__H
#define MOVER__H

#include <vector>
#include "Box.h"

class Mover
{

protected:
    Mover() = default;
    Mover(const Mover& o) = default;
    Mover(Mover&& o) noexcept = default;
    Mover& operator= (const Mover& o) = default;
    Mover& operator= (Mover&& o) noexcept = default;

public:
    virtual ~Mover() noexcept = default;
    
    virtual std::vector<Position> getFuturePositions(const Box* box) = 0;
};

#endif
