#ifndef MOVER_DOWN__H
#define MOVER_DOWN__H

#include "Mover.h"

class Mover_Down : public Mover
{

public:
    std::vector<Position> getFuturePositions(const Box& box) override;
};

#endif
    
