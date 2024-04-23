#ifndef MOVER_REG__H
#define MOVER_REG__H

#include "Board.h"
#include "Box.h"
#include "Mover.h"

// Ensures the order of the addNote() calls to BoardNote. Since Spots can only receive BoardNotes in a certain order.
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
    
    // Calls the Board's addNote() twice, both times using position and the contained boxId. First call uses the SpotType:: to_leave, the second time uses SpotType::left.
    bool removeBox(Position position) override;
   
    // Calls the Board's addNote() method twice, both times using position and the contained boxId. The first call uses SpotType::to_arrive. If that is successful, the thread sleeps for 5ms and the second addNote() is called with SpotType::arrive.
    bool addBox(Position position) override;

    // Calls the Board's addNote() method. Each call uses the contained boxId. The first call uses newPosition and SpotType::to_arrive. If this is not successful the method ends. (May not be successful if the newPosition has a SpotType other than SpotType::left.) If it is successful, addNote() is called with the oldPosition and SpotType::to_leave. Then the current thread sleeps for 14ms if the move is diagonal and 10ms if the move is straight. Then boardNote() is called with the newPosition and SpotType::arrive. Lastly boardNote() is called with the oldPosition and SpotType::left.
    bool moveBox(Position oldPosition, Position newPosition) override;

    int getBoxId() const override;

private:
    
    int _boxId;
    Board* _board;

};

#endif
