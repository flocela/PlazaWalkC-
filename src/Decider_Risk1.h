#ifndef DECIDER_RISK1__H
#define DECIDER_RISK1__H

#include "Decider.h"

/* Named as Risk1 Decider because it will suggest moving to Positions that have a MoveType of MoveType::left and MoveType::to_leave.

Since the MoveType::to_leave means the Position is currently occupied (but will soon be free), Risk1Decider returns a suggested time to arrival of 7 milliseconds when the MoveType is MoveType::to_leave.

If the MoveType is MoveType::left, then it will suggest moving into the Position in zero milliseconds.
*/
class Decider_Risk1 : public Decider
{

    public:

    /*
    Returns true if @position contains a MoveType of MoveType::to_leave or MoveType::left
    */
    bool suggestMoveTo(Position position, const Board& board) override;

   
    /*
    Returns the first Position that contiains a MoveType::to_leave or MoveType::left. If the Position contains MoveType::to_leave, then a time-to-arrival of 7 is returned. If the Position contains MoveType::left, then a time-to-arrival of 0 is returned.
    */
    std::pair<Position, int> getNext(
        const std::vector<Position> possiblePositions,
        const Board& board) override;
};

#endif
