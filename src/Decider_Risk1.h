#ifndef DECIDER_RISK1__H
#define DECIDER_RISK1__H

#include "Decider.h"

/* Named as Risk1 Decider because it will suggest moving to Positions that have a SpotType of SpotType::left and SpotType::to_leave. Since the SpotType::to_leave means the Position is currently occupied (but will soon be free), Risk1Decider returns a suggested time to departure of 7 milliseconds when the SpotType is SpotType::to_leave. If the SpotType is SpotType::left, then it will suggest leaving in zero milliseconds.
*/
class Decider_Risk1 : public Decider
{

    public:

    /*
    Returns true if @position contains a SpotType of SpotType::to_leave or SpotType::left
    */
    bool suggestMoveTo(Position position, const Board& board) override;

   
    /*
    Returns the first Position that contiains a SpotType::to_leave or SpotType::left. If the Position contains SpotType::to_leave, then a time-to-departure of 7 is returned. If the Position contains SpotType::left, then a time-to-departure of 0 is returned.
    */
    std::pair<Position, int> getNext(
        const std::vector<Position>& possiblePositions,
        const Board& board) override;
};

#endif
