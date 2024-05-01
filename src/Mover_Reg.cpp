#include <thread>
#include "Mover_Reg.h"

using namespace std;

Mover_Reg::Mover_Reg(int boxId, Board* board): _boxId{boxId}, _board{board} {}
    
int Mover_Reg::getBoxId() const
{
    return _boxId;
}

bool Mover_Reg::addBox(Position position)
{
    bool success = _board->addNote(position, BoardNote{_boxId, SpotType::to_arrive});

    if (success)
    {
        this_thread::sleep_for(5ms);
        _board->addNote(position, BoardNote{_boxId, SpotType::arrive});
    }
   
    return success;
}

bool Mover_Reg::removeBox(Position position)
{
    bool success = false;

    success = _board->addNote(position, BoardNote{_boxId, SpotType::to_leave});
    success = _board->addNote(position, BoardNote{_boxId, SpotType::left});

    return success;
}

bool Mover_Reg::moveBox(Position oldPosition, Position newPosition)
{
    bool success = _board->addNote(newPosition, BoardNote{_boxId, SpotType::to_arrive});
    if (success)
    {
        _board->addNote(oldPosition, BoardNote{_boxId, SpotType::to_leave});

        int deltaX = oldPosition.getX() - newPosition.getX();
        int deltaY = oldPosition.getY() - newPosition.getY(); 
        if( ( (deltaX * deltaX) + (deltaY * deltaY)) == 2 )
        {
            this_thread::sleep_for(14ms);
        }
        else
        {
            this_thread::sleep_for(10ms);
        }

        _board->addNote(newPosition, BoardNote{_boxId, SpotType::arrive});
        _board->addNote(oldPosition, BoardNote{_boxId, SpotType::left});
    
    }
   
    return success;
}


