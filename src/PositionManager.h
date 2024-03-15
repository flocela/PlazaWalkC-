#ifndef POSITION_MANAGER__H
#define POSITION_MANAGER__H

#include <vector>
#include "Box.h"
#include "Position.h"

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

    virtual bool atEnd(Position position) = 0;    
    virtual std::vector<Position> getFuturePositions(Position position) = 0;
    virtual std::pair<Position, Position> getEndPoint() const = 0;
};

#endif
