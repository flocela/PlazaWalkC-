#include <thread>
#include "Mover_Reg.h"
#include "BoardNote.h"
#include "BoxNote.h"

using namespace std;

Mover_Reg::Mover_Reg(Box& box, Board& board): _box{box}, _board{board} {}

void Mover_Reg::addBox(Position position)
{
    int boxId = _box.getId();
    _board.addNote(position, BoardNote{2, boxId});
    
    this_thread::sleep_for(5ms);

    _board.addNote(position, BoardNote{4, boxId});
}

void Mover_Reg::moveBox(Position position)
{
    int boxId = _box.getId();
    Position oldPosition = _box.getPosition();
       
    _board.addNote(position, BoardNote{2, boxId});
    _board.addNote(oldPosition, BoardNote{1, boxId});
    
    this_thread::sleep_for(5ms);

    _board.addNote(oldPosition, BoardNote{3, boxId});
    _board.addNote(position, BoardNote{4, boxId});
}


