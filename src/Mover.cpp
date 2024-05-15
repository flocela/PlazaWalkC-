#include "Mover.h"
#include <thread> 

using namespace std;

Mover::Mover(int boxId, Board* board): _boxId{boxId}, _board{board} {}

int Mover::getBoxId() const
{
    return _boxId;
}

bool Mover::moveBox(Position oldPosition, Position newPosition)
{
    bool success = _board->changeSpot(newPosition, BoardNote{_boxId, MoveType::to_arrive}, true);
    if (success)
    {
        _board->changeSpot(oldPosition, BoardNote{_boxId, MoveType::to_leave}, true);

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

        _board->changeSpot(newPosition, BoardNote{_boxId, MoveType::arrive}, true);
        _board->changeSpot(oldPosition, BoardNote{_boxId, MoveType::left}, true);
    
    }
   
    return success;
}

bool Mover::addBox(Position position)
{
    bool success = _board->changeSpot(position, BoardNote{_boxId, MoveType::to_arrive}, false);

    if (success)
    {
        this_thread::sleep_for(5ms);
        _board->changeSpot(position, BoardNote{_boxId, MoveType::arrive}, true);
    }
   
    return success;
}

bool Mover::removeBox(Position position)
{
    bool success = false;

    success = _board->changeSpot(position, BoardNote{_boxId, MoveType::to_leave}, true);
    success = _board->changeSpot(position, BoardNote{_boxId, MoveType::left}, true);

    return success;
}

