#ifndef POSITION_MANAGER__H
#define POSITION_MANAGER__H

#include <vector>
#include "Position.h"
#include "Rectangle.h"

/*
Returns whether a Box has reached its final destination.
Suggests possible next Positions for a Box.
*/
class PositionManager
{

    protected:

    PositionManager() = default;
    PositionManager(const PositionManager& o) = default;
    PositionManager(PositionManager&& o) noexcept = default;
    PositionManager& operator= (const PositionManager& o) = default;
    PositionManager& operator= (PositionManager&& o) noexcept = default;


    public:
    virtual ~PositionManager() noexcept = default;

    /*
    Returns true if @position is at the PositionManager's final destination.
    */ 
    virtual bool atEnd(Position position) = 0;

    /*
    Returns a vector of Positions that are recomended for the Box at Position @position. The Positions are in order of most recommended to least recommended. If no Position is recommended, then returns an empty vector.
    */
    virtual std::vector<Position> getFuturePositions(Position position) = 0;

    /*
    Returns the final destination of the PositionManager as a Rectangle. It could be that the Rectangle has an area of zero. Then the final destination is just one Position.
    */
    virtual Rectangle getEndRect() const = 0;
};

#endif
