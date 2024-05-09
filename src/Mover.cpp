#include "Mover.h"

Mover::Mover(int boxId, Board* board): _boxId{boxId}, _board{board} {}

int Mover::getBoxId() const
{
    return _boxId;
}

bool Mover::moveBox(Position oldPosition, Position newPosition)
{
    bool success = _board->addNote(newPosition, BoardNote{_boxId, SpotType::to_arrive}, true);
    if (success)
    {
        _board->addNote(oldPosition, BoardNote{_boxId, SpotType::to_leave}, true);

        int deltaX = oldPosition.getX() - newPosition.getX();
        int deltaY = oldPosition.getY() - newPosition.getY(); 
        if( ( (deltaX * deltaX) + (deltaY * deltaY)) == 2 )
        {
           sleepForDiagonalMove(); 
        }
        else
        {
           sleepForLateralMove();
        }

        _board->addNote(newPosition, BoardNote{_boxId, SpotType::arrive}, true);
        _board->addNote(oldPosition, BoardNote{_boxId, SpotType::left}, true);
    
    }
   
    return success;
}


