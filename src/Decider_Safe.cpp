#include "Decider_Safe.h"

using namespace std;

Position Decider_Safe::getNextPosition(
    vector<Position> possiblePositions,
    const Board& board,
    unordered_map<int, Box*> boxesPerBoxId)
{
    (void)possiblePositions;
    (void) board;
    (void) boxesPerBoxId;
    for (const Position& position : possiblePositions)
    {
        unordered_map<int, BoardNote> boardNotesPerBoxId = board.getNotes(position);

        bool isOccupied = false;
        for (const auto& boxIdAndBoardNote : boardNotesPerBoxId)
        {
            int boxId = boxIdAndBoardNote.first;
            if (boxesPerBoxId.find(boxId) != boxesPerBoxId.end())
            {
                isOccupied = true;
                break;
            }
        }
        if (!isOccupied)
        {
            return position;
        }
    }
    
    return Position{-1, -1};
} 

