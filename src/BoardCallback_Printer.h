#ifndef BOARDCALLBACK_PRINTER__H
#define BOARDCALLBACK_PRINTER__H

#include <vector>
#include "Board.h"
#include "BoardCallback.h"
#include "Printer.h"

class BoardCallback_Printer : public BoardCallback
{
public:
    // TODO this hsould be a const Board
    BoardCallback_Printer(Board* board, Printer* printer);
    BoardCallback_Printer() = delete;
    BoardCallback_Printer(const BoardCallback_Printer& o) = delete;
    BoardCallback_Printer(BoardCallback_Printer&& o) noexcept = delete;
    BoardCallback_Printer& operator=(const BoardCallback_Printer& o) = delete;
    BoardCallback_Printer& operator=(BoardCallback_Printer&& o) noexcept = delete;
    ~BoardCallback_Printer() noexcept = default;

    void callback(BoardNote boardNote, Position position) override;

private:
    const Board* _board;
    Printer* _printer;
};

#endif
