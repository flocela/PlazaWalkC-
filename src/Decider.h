#ifndef DECIDER__H
#define DECIDER__H

#include <vector>
#include "Board.h"

/*
Returns a decision on whether a Box should move to Position, or chooses which is the best Position to move to.
*/
class Decider
{

    public:

    virtual ~Decider() = default;

    /*
    Returns a decistion on whether the user should move to @position, given @position and @board.
    */
    virtual bool suggestMoveTo(Position position, const Board& board) = 0;

    /*
    Retuns the suggested Position to move to given @possiblePositions and @board. Also returns the number of millisecondsto wait before moving to the returned Position.
    */
    virtual std::pair<Position, int> getNext(
        const std::vector<Position> possiblePositions,
        const Board& board) = 0;

};

#endif
