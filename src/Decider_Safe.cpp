#include "Decider_Safe.h"

#include "SpotType.h"

using namespace std;

Position Decider_Safe::getNextPosition(
    vector<Position> possiblePositions,
    const Board& board
    )
{
    // Take each position in possiblePositions
//    char x = (rand()%25) + 65;
 //   cout << x << "s"<< possiblePositions.size() << endl;
    for (const Position& position : possiblePositions)
    {
  //      cout << x << position<< ", ";
        // BoardNote at position will tell us what box (if any) is currently at that position. 
        BoardNote boardNote = board.getNoteAt(position);

        // if the BoardNote's type is empty, then return current position. 
        if (boardNote.getType() == SpotType::left)
        {
   //         cout << x << "return"<<position;
            return position;
        }       
    }
   // cout << x << "{-1, -1}" << endl;

    return Position{-1, -1};
} 

