#include "Decider_Risk1.h"

#include "SpotType.h"
#include "Util.h"

using namespace std;

bool Decider_Risk1::suggestMoveTo(Position position, const Board& board)
{
    BoardNote note = board.getNoteAt(position);
    return ((note.getType() == SpotType::left) ||
           (note.getType() == SpotType::to_leave));
}

pair<Position, int> Decider_Risk1::getNext(
    const vector<Position>& possiblePositions,
    const Board& board
    )
{
    // Take each position in possiblePositions
    for (const Position& position : possiblePositions)
    {
        // BoardNote at position will tell us what box (if any) is currently at that position. 
        BoardNote boardNote = board.getNoteAt(position);

        if (boardNote.getType() == SpotType::left)
        {
            return {position, 0};
        }
        if (boardNote.getType() == SpotType::to_leave)
        {
            return {position, 7};
        }
    }

    return {Position{-1, -1}, -1};
} 

