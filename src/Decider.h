#ifndef DECIDER__H
#define DECIDER__H

#include <vector>
#include "Board.h"

class Decider
{

public:
    virtual ~Decider() = default;
    //TODO test moveTo and addToBoard methods
    virtual bool addToBoard(Position position, const Board& board) = 0;
    virtual std::pair<Position, int> getNextPosition(
        std::vector<Position> possiblePositions,
        const Board& board) = 0;

};

#endif
