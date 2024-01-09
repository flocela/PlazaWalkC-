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
    _box.addNote(BoxNote{10, position, position, std::chrono::high_resolution_clock::now()});
    
    this_thread::sleep_for(5ms);

    _box.addNote(BoxNote{11, position, position, std::chrono::high_resolution_clock::now()});
    _board.addNote(position, BoardNote{4, boxId});
}

void Mover_Reg::moveBox(Position position)
{
    int boxId = _box.getId();
    Position oldPosition = _box.getPos(std::chrono::high_resolution_clock::now());
       
    _board.addNote(position, BoardNote{2, boxId});
    _board.addNote(oldPosition, BoardNote{1, boxId});
    _box.addNote(BoxNote{10, position, oldPosition, std::chrono::high_resolution_clock::now()});
    
    this_thread::sleep_for(5ms);

    _box.addNote(BoxNote{11, position, oldPosition, std::chrono::high_resolution_clock::now()});
    _board.addNote(oldPosition, BoardNote{3, boxId});
    _board.addNote(position, BoardNote{4, boxId});
}


