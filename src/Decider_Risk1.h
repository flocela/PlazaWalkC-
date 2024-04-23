#ifndef DECIDER_RISK1__H
#define DECIDER_RISK1__H

#include "Decider.h"

class Decider_Risk1 : public Decider
{
public:
    
    bool addToBoard(Position position, const Board& board) override;
    std::pair<Position, int> getNext(
        const std::vector<Position>& possiblePositions,
        const Board& board) override;
};

#endif
