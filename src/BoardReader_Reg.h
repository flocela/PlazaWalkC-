#ifndef BOARDREADER_REG__H
#define BOARDREADER_REG__H

#include "Board.h"
#include "BoardReader.h"

class BoardReader_Reg : public BoardReader
{

public:
    
    BoardReader_Reg(const Board& board);
    BoardReader_Reg(const BoardReader_Reg& board) = delete;
    BoardReader_Reg(BoardReader_Reg&& o) noexcept = delete;
    BoardReader_Reg& operator=(const BoardReader_Reg& board) = delete;
    BoardReader_Reg& operator=(BoardReader_Reg&& o) noexcept = delete;
    ~BoardReader_Reg() noexcept = default; 

    int getWidth() const override;
    int getHeight() const override;

    std::unordered_map<int, BoardNote> getNotes(Position position) const override;  

private:

    const Board& _board;

    
};

#endif
