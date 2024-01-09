#include "Decider_Safe.h"

using namespace std;

Position Decider_Safe::getNextPosition(
    vector<Position> possiblePositions,
    const Board& board,
    unordered_map<int, Box*> boxesPerBoxId)
{
    // Take each position in possiblePositions
    for (const Position& position : possiblePositions)
    {
        bool isOccupied = false;
       
        // Each boxId in boardNotesPerBoxId represents a box that may be at position. 
        unordered_map<int, BoardNote> boardNotesPerBoxId = board.getNotes(position);

        // Take each boxId associated with position and compare box's current position with position
        for (const auto& boxIdAndBoardNote : boardNotesPerBoxId)
        {
            int boxId = boxIdAndBoardNote.first;
            if (boxesPerBoxId.find(boxId) != boxesPerBoxId.end())
            {
                if (boxesPerBoxId.at(boxId)->getPos(std::chrono::high_resolution_clock::now()) == position)
                {
                    isOccupied = true;
                    break;
                }
            }
        }
        if (!isOccupied)
        {
            return position;
        }
    }
    
    return Position{-1, -1};
} 

