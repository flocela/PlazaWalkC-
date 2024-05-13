#include <thread>
#include "Mover_Reg.h"

using namespace std;

Mover_Reg::Mover_Reg(int boxId, Board* board):
Mover(boxId, board)
{}


void Mover_Reg::sleepForDiagonalMove()
{
    this_thread::sleep_for(10ms);
}

void Mover_Reg::sleepForLateralMove()
{
    this_thread::sleep_for(14ms);
}
