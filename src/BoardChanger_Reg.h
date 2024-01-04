#ifndef BOARDCHANGER_REG__H
#define BOARDCHANGER_REG__H

#include "BoardChanger.h"
#include "Position.h"
#include "Board.h"
#include "BoardNote.h"

class BoardChanger_Reg : public BoardChanger
{

public:

    BoardChanger_Reg(Board& board);
    BoardChanger_Reg(const BoardChanger_Reg&) = delete;
    BoardChanger_Reg(BoardChanger&& o) noexcept = delete;
    BoardChanger_Reg& operator=(const BoardChanger_Reg& o) = delete;
    BoardChanger_Reg& operator=(BoardChanger&& o) noexcept = delete;
    ~BoardChanger_Reg() noexcept = default;

    void addNote(Position position, BoardNote boardNote) override;

private:

    Board& _board;
};

#endif
