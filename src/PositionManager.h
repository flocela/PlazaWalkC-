#ifndef POSITION_MANAGER__H
#define POSITION_MANAGER__H

#include <vector>
#include "Box.h"
#include "Position.h"
#include "Rectangle.h"

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

    // Returns true if Position is at PositionManager's final destination.
    virtual bool atEnd(Position position) = 0;

    // Returns a vector of Positions, in order of most recommended to least recommended. If no Position is recommended, then returns an empty vector.    
    virtual std::vector<Position> getFuturePositions(Position position) = 0;

    // Returns the final destination of the PositionManager as a rectangle. The rectangle is represented as a pair of Positions, where the first Position is the top left corner of the rectangle and the second Position is the bottom right corner.
    virtual Rectangle getEndPoint() const = 0;
};

#endif
