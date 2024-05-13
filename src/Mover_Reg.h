#ifndef MOVER_REG__H
#define MOVER_REG__H

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
    
    void sleepForDiagonalMove() override;

    void sleepForLateralMove() override;


};

#endif
