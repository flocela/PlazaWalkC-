#include "BoardReader_Reg.h"

using namespace std;

BoardReader_Reg::BoardReader_Reg(const Board& board):_board{board}{}

int BoardReader_Reg::getWidth() const
{
    return _board.getWidth();
}

int BoardReader_Reg::getHeight() const
{
    return _board.getHeight();
}

unordered_map<int, BoardNote> BoardReader_Reg::getNotes(Position position) const
{
    return _board.getNotes(position);
}
