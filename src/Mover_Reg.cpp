#include <thread>
#include "Mover_Reg.h"

using namespace std;

Mover_Reg::Mover_Reg(Box& box, Board& board): _box{box}, _board{board} {}

// TODO this return value needs to be tested.
bool Mover_Reg::addBox(Position position)
{
    int boxId = _box.getId();
    bool success = _board.addNote(position, BoardNote{boxId, 2});

    if (success)
    {
        this_thread::sleep_for(5ms);
        _board.addNote(position, BoardNote{boxId, 4});
    }
   
    return success;
}

// TODO this return value needs to be tested. Along with the order of these moves.
bool Mover_Reg::moveBox(Position oldPosition, Position newPosition)
{
    int boxId = _box.getId();
    if (boxId == 0)
    {
        cout << "Mover_Reg: box 0 moving to " << newPosition << endl;
    }
       
    bool success = _board.addNote(newPosition, BoardNote{boxId, 2});
    if (success)
    {
        _board.addNote(oldPosition, BoardNote{boxId, 1});
        
        this_thread::sleep_for(5ms);

        _board.addNote(newPosition, BoardNote{boxId, 4});
        _board.addNote(oldPosition, BoardNote{boxId, 3});
    
    }
   
    return success;
}


