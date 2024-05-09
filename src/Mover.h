#ifndef MOVER__H
#define MOVER__H

#include "Board.h"

#include "Position.h"

/*
Adds Boxes to a Board.
Removes Boxes from a Board.
Moves Boxes on the Board.
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
    Adds a Box to the Board at @position. If this addition is unsuccessful, neither Boxes' levels go up.
    */
    virtual bool addBox(Position position) = 0;

    virtual bool removeBox(Position position) = 0;

    /*
    Moves a Box on the Board from @oldPosition to @newPosition. If the move is unsuccessful, both Boxes' levels to up by one.
     In order to move a Box calls the Board's addNote() method with @oldPosition and @newPosition and the correct boxId and SpotTypes. Each call uses the contained boxId.
    
    The first call uses @newPosition and SpotType::to_arrive. If this is not successful the method returns false. (It will not be successful if @newPosition has a SpotType other than SpotType::left.)

    If it is successful, addNote() is called with the oldPosition and SpotType::to_leave.

    Then the current thread sleeps for the time specified in sleepForDiagonalMove() or sleepForLateralMove().

    Then addNote() is called with the @newPosition and SpotType::arrive.

    Lastly addNote() is called with the @oldPosition and SpotType::left.

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
