#ifndef MOVER_REG__H
#define MOVER_REG__H

#include "Board.h"
#include "Box.h"
#include "Mover.h"

class Mover_Reg : public Mover
{

public:
    Mover_Reg(Box& box, Board& board);
    Mover_Reg() = delete;
    Mover_Reg(const Mover_Reg& o) = delete;
    Mover_Reg(Mover_Reg&& o) noexcept = delete;
    Mover_Reg& operator=(const Mover_Reg& o) = delete;
    Mover_Reg& operator=(Mover_Reg&& o) noexcept = delete;
    ~Mover_Reg() noexcept = default;

    bool addBox(Position position) override;
    
    bool moveBox(Position oldPosition, Position newPosition) override;

private:
    
    Box& _box;
    Board& _board;

};

#endif
