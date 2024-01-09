#ifndef DECIDER__H
#define DECIDER__H

#include <unordered_map>
#include <vector>
#include "Board.h"

class Decider
{

public:
    virtual Position getNextPosition(
        std::vector<Position> possiblePositions,
        const Board& board,
        std::unordered_map<int, Box*> boxesPerBoxId) = 0;

};

#endif
