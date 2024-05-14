#include "Decider_Safe.h"

#include "SpotType.h"
#include "Util.h"

using namespace std;

bool Decider_Safe::suggestMoveTo(Position position, const Board& board)
{
    return board.getNoteAt(position).getType() == SpotType::left;
}

pair<Position, int> Decider_Safe::getNext(
    const vector<Position> possiblePositions,
    const Board& board)
{
    for (const Position& position : possiblePositions)
    {
        // BoardNote at position. 
        BoardNote boardNote = board.getNoteAt(position);

        // If the BoardNote's type is empty, then return position. 
        if (boardNote.getType() == SpotType::left)
        {
            return {position, 0};
        }       
    }

    // @possiblePositions did not hold a Position with a SpotType of SpotType::left. Return an invalid Position and a time of -1.
    return {Position{-1, -1}, -1};
} 

