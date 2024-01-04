#include "BoardChanger_Reg.h"

BoardChanger_Reg::BoardChanger_Reg(Board& board):_board(board) {}

void BoardChanger_Reg::addNote(Position position, BoardNote boardNote)
{
    _board.addNote(position, boardNote);
}
