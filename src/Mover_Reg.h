#ifndef MOVER_REG__H
#define MOVER_REG__H

#include "Mover.h"

/*
Requirements for a Box to take up a new Position on the Board: 1)The Board must receive a BoardNote with the boxId, the new Position, and a SpotType::to_arrive. 2)Then the Board must receive a BoardNote with the boxId, the new Position, and a SpotType::arrive.

For a Box to leave a Position. 1)The Board must receive a BoardNote with the boxId, the old Position, and the SpotType::to_leave. 1)Then the Board must receve a BoardNote with the boxId, the old Position, and the SpotType::left.

Mover_Reg assures that these steps are taken in a particular order. First the Board receives the BoardNote with SpotType::to_arrive, then with SpotType::to_leave, then SpotType::arrive, and finally SpotType::left. Notice that the Box will be occupying two Positions from SpotType::to_arrive to until SpotType::left.

Mover_Reg holds one boxId, so it can only ever move one Box.
*/
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
    
    /*
    Calls the Board's addNote() twice, both times using @position and the contained boxId. First call uses the SpotType::to_leave, the second time uses SpotType::left. If both calls are successful, then returns true, otherwise returns false. Should always return true, because a Box can always move away from a Position.
    */
    bool removeBox(Position position) override;
   
    /*
    Calls the Board's addNote() method twice, both times using @position and the contained boxId. The first call uses SpotType::to_arrive. If that is successful, the thread sleeps for 5ms and the second addNote() is called with SpotType::arrive. The first call may be unsuccessful if a Box is already at @position.
    */
    bool addBox(Position position) override;

    void sleepForDiagonalMove() override;

    void sleepForLateralMove() override;


};

#endif
