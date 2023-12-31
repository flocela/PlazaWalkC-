#ifndef MOVER_UP__H
#define MOVER_UP__H

#include "Mover.h"

class Mover_Up : public Mover
{

public:
    std::vector<Position> getFuturePositions(const Box& box) override;
};

#endif
