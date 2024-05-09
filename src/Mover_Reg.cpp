#include <thread>
#include "Mover_Reg.h"

using namespace std;

Mover_Reg::Mover_Reg(int boxId, Board* board):
Mover(boxId, board)
{}

bool Mover_Reg::addBox(Position position)
{
    bool success = _board->changeSpot(position, BoardNote{_boxId, SpotType::to_arrive}, false);

    if (success)
    {
        this_thread::sleep_for(5ms);
        _board->changeSpot(position, BoardNote{_boxId, SpotType::arrive}, true);
    }
   
    return success;
}

bool Mover_Reg::removeBox(Position position)
{
    bool success = false;

    success = _board->changeSpot(position, BoardNote{_boxId, SpotType::to_leave}, true);
    success = _board->changeSpot(position, BoardNote{_boxId, SpotType::left}, true);

    return success;
}

void Mover_Reg::sleepForDiagonalMove()
{
    this_thread::sleep_for(10ms);
}

void Mover_Reg::sleepForLateralMove()
{
    this_thread::sleep_for(14ms);
}
