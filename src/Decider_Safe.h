#ifndef DECIDER_SAFE__H
#define DECIDER_SAFE__H

#include "Decider.h"

class Decider_Safe : public Decider
{
public:
    Position getNextPosition(
        std::vector<Position> possiblePositions,
        const Board& board) override;
};


#endif
