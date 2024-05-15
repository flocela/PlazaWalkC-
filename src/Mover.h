#ifndef MOVER__H
#define MOVER__H

#include "Board.h"

#include "Position.h"

/*
Adds Boxes to a Board.
Removes Boxes from a Board.
Moves Boxes on the Board.

Requirements for a Box to take up a new Position on the Board: 1)The Board must receive a BoardNote with the boxId, the new Position, and a MoveType::to_arrive. 2)Then the Board must receive a BoardNote with the boxId, the new Position, and a MoveType::arrive.

For a Box to leave a Position. 1)The Board must receive a BoardNote with the boxId, the old Position, and the MoveType::to_leave. 1)Then the Board must receve a BoardNote with the boxId, the old Position, and the MoveType::left.

Mover assures that these steps are taken in a particular order. First the Board receives the BoardNote with MoveType::to_arrive, then with MoveType::to_leave, then MoveType::arrive, and finally MoveType::left. Notice that the Box will be occupying two Positions from MoveType::to_arrive to until MoveType::left.

Mover_Reg holds one boxId, so it can only ever move one Box.
*/

class Mover
{

protected:
    Mover(int boxId, Board* board);
    Mover() = delete;
    Mover(const Mover& o) = default;
    Mover(Mover&& o) noexcept = default;
    Mover& operator=(const Mover& o) = default;
    Mover& operator=(Mover&& o) noexcept = default;

    int _boxId;
    Board* _board;

public:

    virtual ~Mover () noexcept = default;

    /*
    Adds a Box to the Board at @position.

    Calls the Board's addNote() twice, both times using @position and the contained boxId. First call uses the MoveType::to_leave, the second time uses MoveType::left. If both calls are successful, then returns true, otherwise returns false. Should always return true, because a Box can always move away from a Position.
    */
    bool addBox(Position position);

    /*
    Removes the Box to the Board at @position.

    Calls the Board's addNote() method twice, both times using @position and the contained boxId. The first call uses MoveType::to_arrive. If that is successful, the thread sleeps for 5ms and the second addNote() is called with MoveType::arrive. The first call may be unsuccessful if a Box is already at @position.
    */
    bool removeBox(Position position);

    /*
    Moves a Box on the Board from @oldPosition to @newPosition. If the move is unsuccessful, both Boxes' levels to up by one.
     In order to move a Box calls the Board's addNote() method with @oldPosition and @newPosition and the correct boxId and MoveTypes. Each call uses the contained boxId.
    
    The first call uses @newPosition and MoveType::to_arrive. If this is not successful the method returns false. (It will not be successful if @newPosition has a MoveType other than MoveType::left.)

    If it is successful, addNote() is called with the oldPosition and MoveType::to_leave.

    Then the current thread sleeps for the time specified in sleepForDiagonalMove() or sleepForLateralMove().

    Then addNote() is called with the @newPosition and MoveType::arrive.

    Lastly addNote() is called with the @oldPosition and MoveType::left.

    If all the addNote() calls are successful, returns true.
    */
    bool moveBox(Position oldPosition, Position newPosition);

    /*
    Called inside moveBox(). If the move is a diagonal move then sleepForDiagonalMove() is called. It is provided to add a wait time for a diagonal move (which is generally thought of as taking more time than a lateral move.)
    */
    virtual void sleepForDiagonalMove() = 0;

    /*
    Called inside moveBox(). If the move is a lateral move then sleepForLateralMove() is called. It is provided to add a wait time for a lateral move (which is generally thought of as taking less time than a diagonal move.)
    */
    virtual void sleepForLateralMove() = 0;

    int getBoxId() const;

};

#endif
