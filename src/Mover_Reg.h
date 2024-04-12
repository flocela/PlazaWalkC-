#ifndef MOVER_REG__H
#define MOVER_REG__H

#include "Board.h"
#include "Box.h"
#include "Mover.h"

class Mover_Reg : public Mover
{

public:
    Mover_Reg(int boxId, Board* board);
    Mover_Reg() = delete;
    Mover_Reg(const Mover_Reg& o) = default;
    Mover_Reg(Mover_Reg&& o) noexcept = default;
    Mover_Reg& operator=(const Mover_Reg& o) = default;
    Mover_Reg& operator=(Mover_Reg&& o) noexcept = default;
    ~Mover_Reg() noexcept = default;

    bool removeBox(Position position) override;
    bool addBox(Position position) override;
    bool moveBox(Position oldPosition, Position newPosition) override;
    int getBoxId() const override;

private:
    
    int _boxId;
    Board* _board;

};

#endif
