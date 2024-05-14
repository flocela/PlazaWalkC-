#ifndef DECIDER_SAFE__H
#define DECIDER_SAFE__H

#include "Decider.h"

/*
Named a safe Decider because it will only suggest moving to Positions that do not have a Box currently in them. In other words it will only suggest Positions that are empty on the Board.
*/
class Decider_Safe : public Decider
{
    public:

    /*
    Only returns true, signalling it is okay to move to @position if @position is empty on Board. Returns true if Spot at @position has a SpotType of SpotType::left. Otherwise returns false.
    */
    bool suggestMoveTo(Position position, const Board& board) override;

    /*
    Will return the first Position in @possiblePositions that has a SpotType of SpotType::left. Along with the Position will return a time to wait of zero. If no Position has a SpotType of SpotType::left, then returns a Position of {-1, -1} and a time of -1.
    */
    std::pair<Position, int> getNext(
        const std::vector<Position> possiblePositions,
        const Board& board) override;
};


#endif
