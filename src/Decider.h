#ifndef DECIDER__H
#define DECIDER__H

#include <vector>
#include "Board.h"

class Decider
{

    public:

    virtual ~Decider() = default;

    /*
    Returns whether given @position and @board, if the user should move to @position.
    */
    virtual bool suggestMoveTo(Position position, const Board& board) = 0;

    /*
    Retuns the suggested Position to move to given @possiblePositions and @board. Also returns the number of millisecondsto wait before moving to the returned Position.
    */
    virtual std::pair<Position, int> getNext(
        const std::vector<Position>& possiblePositions,
        const Board& board) = 0;

};

#endif
