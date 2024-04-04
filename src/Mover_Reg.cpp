#include <thread>
#include "Mover_Reg.h"

using namespace std;

Mover_Reg::Mover_Reg(int boxId, Board* board): _boxId{boxId}, _board{board} {}

// TODO this return value needs to be tested.
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
// TODO test exceptions
bool Mover_Reg::removeBox(Position position)
{
    BoardNote fromBoard = _board->getNoteAt(position);

    if (fromBoard.getBoxId() != _boxId)
    {
        string invalidString = "Trying to remove box ";
        invalidString.append(to_string(_boxId));
        invalidString.append(" but box with id of ");
        invalidString.append(to_string(fromBoard.getBoxId()));
        invalidString.append(" is at position [");
        invalidString.append(to_string(position.getX()));
        invalidString.append(", ");
        invalidString.append(to_string(position.getY()));
        invalidString.append("].");
       throw invalid_argument(invalidString); 
    }
    
    bool success = _board->addNote(position, BoardNote{_boxId, SpotType::to_leave});
    if (!success)
    {
        string invalidString = "Trying to remove box ";
        invalidString.append(to_string(_boxId));
        invalidString.append(", but Board would not accept SpotType::to_leave at position [");
        invalidString.append(to_string(position.getX()));
        invalidString.append(", ");
        invalidString.append(to_string(position.getY()));
        invalidString.append("].");
        throw invalid_argument(invalidString);
    }

    success = _board->addNote(position, BoardNote{_boxId, SpotType::left});
    if (!success)
    {
        string invalidString = "Trying to remove box ";
        invalidString.append(to_string(_boxId));
        invalidString.append(", but Board would not accept SpotType::to_leave at position [");
        invalidString.append(to_string(position.getX()));
        invalidString.append(", ");
        invalidString.append(to_string(position.getY()));
        invalidString.append("].");
        throw invalid_argument(invalidString);
    }
    return true;
}

// TODO this return value needs to be tested. Along with the order of these moves.
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


