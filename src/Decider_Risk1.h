#ifndef DECIDER_RISK1__H
#define DECIDER_RISK1__H

#include "Decider.h"

class Decider_Risk1 : public Decider
{
public:

    // Returns true if position contains a SpotType::to_leave or SpotType::left
    bool suggestMoveTo(Position position, const Board& board) override;

   
    // Returns the first Position that contiains a SpotType::to_leave or SpotType::left. If the Position contains SpotType::to_leave,then a time-to-departure of 7 is returned. If the Position contains SpotType::left, then a time-to-departure of 0 is returned. 
    std::pair<Position, int> getNext(
        const std::vector<Position>& possiblePositions,
        const Board& board) override;
};

#endif
