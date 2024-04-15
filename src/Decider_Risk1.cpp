#include "Decider_Risk1.h"

#include "SpotType.h"
#include "Util.h"

using namespace std;

bool Decider_Risk1::addToBoard(Position position, const Board& board)
{
    return board.getNoteAt(position).getType() == SpotType::left;
}

bool Decider_Risk1::moveTo(Position position, const Board& board)
{
    BoardNote note = board.getNoteAt(position);
    if(note.getType() == SpotType::left)
    {
        return true;
    }
    else if(note.getType() == SpotType::to_leave)
    {
       return Util::getRandom(0, 100) < 25;
    }
    else
    {
        return false;
    }
}

Position Decider_Risk1::getNextPosition(
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
        if (boardNote.getType() == SpotType::left || 
            boardNote.getType() == SpotType::to_leave)
        {
   //         cout << x << "return"<<position;
            return position;
        }       
    }
   // cout << x << "{-1, -1}" << endl;

    return Position{-1, -1};
} 

