#include "Mover_Down.h"

using namespace std;

vector<Position> Mover_Down::getFuturePositions(const Box* box)
{
    Position curPosition = Position{-1, -1};
    
    vector<BoxNote> notes = box->getLastNotes(5);
    for (auto it = notes.rbegin(); it != notes.rend(); ++it)
    {
        if ((*it).getType() == 4)
        {
            curPosition = Position{(*it).getToPosition()};
            break;
        }
    }
   
    // TODO could fall off the array. 
    vector<Position> newPositions{
        Position{curPosition.getX(), curPosition.getY()+1},
        Position{curPosition.getX()+1, curPosition.getY()+1},
        Position{curPosition.getX()-1, curPosition.getY()+1}};

    return newPositions;
}    
    
            
     
