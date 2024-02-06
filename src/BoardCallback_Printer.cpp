#include "BoardCallback_Printer.h"

// TODO this should be a const Board
BoardCallback_Printer::BoardCallback_Printer(Board* board, Printer* printer)
:   _board{board},
    _printer{printer}
{}

void BoardCallback_Printer::callback(BoardNote boardNote, Position position)
{
    (void) boardNote;
    _printer->print(*_board, position);
}
