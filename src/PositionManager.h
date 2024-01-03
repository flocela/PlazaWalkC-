#ifndef POSITION_MANAGER__H
#define POSITION_MANAGER__H

#include <vector>
#include "Box.h"

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
    
    virtual std::vector<Position> getFuturePositions(const Box& box) = 0;
};

#endif
