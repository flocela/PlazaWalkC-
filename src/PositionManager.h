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
    Returns a vector of Positions that are recomended for a Box at Position @position. The Positions are in order of most recommended to least recommended. If no Position is recommended, then returns an empty vector.
    */
    virtual std::vector<Position> getFuturePositions(Position position) = 0;
    
    /*
    Returns true if @position is at the PositionManager's end destination.
    */ 
    virtual bool atEnd(Position position) const = 0;

    /*
    Returns the Rectangle that if a Box was inside this Rectangle it would be at its end Position. It could be that the Rectangle has an area of zero. Then the end Rectangle is just one Position. Being inside a Rectangle means inclusively in the x and y ranges that the top left corner and bottom right corner make.
    */
    virtual Rectangle getEndRect() const = 0;

    /*
    Returns the final target of the PositionManager. This is the Position the Box is targeting. It may very well reach the end rectangle before reaching its target destination.
    */
    virtual Rectangle getTargetRect() const = 0;
};

#endif
