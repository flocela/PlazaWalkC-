#ifndef DECIDER__H
#define DECIDER__H

#include <vector>
#include "Board.h"

class Decider
{

public:
    virtual ~Decider() = default;

    // Returns whether this Decider suggests moving to the given Position. True means yes move, false means don't move.
    virtual bool addToBoard(Position position, const Board& board) = 0;

    // Retuns this Decider's suggested Position to move to from the given vector of possiblePositions, and how long the Box should wait before moving to that Position.
    virtual std::pair<Position, int> getNext(
        const std::vector<Position>& possiblePositions,
        const Board& board) = 0;

};

#endif
