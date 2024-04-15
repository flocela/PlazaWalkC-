#ifndef DECIDER_SAFE__H
#define DECIDER_SAFE__H

#include "Decider.h"

class Decider_Safe : public Decider
{
public:
    bool addToBoard(Position position, const Board& board) override;
    std::pair<Position, int> getNextPosition(
        std::vector<Position> possiblePositions,
        const Board& board) override;
};


#endif
