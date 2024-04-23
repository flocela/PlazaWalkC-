#ifndef DECIDER_SAFE__H
#define DECIDER_SAFE__H

#include "Decider.h"

class Decider_Safe : public Decider
{
    public:

    // If position is designated as Spot::left, then returns true. Otherwise returns false.
    bool suggestMoveTo(Position position, const Board& board) override;

    // Receives a vector of possible Positions to choose from. Assumes that the first Positions are more desirable than later positions.
    // Goes through the Positions in order. If a Position has a SpotType::left, then returns that Position with a time of zero. 
    std::pair<Position, int> getNext(
        const std::vector<Position>& possiblePositions,
        const Board& board) override;
};


#endif
