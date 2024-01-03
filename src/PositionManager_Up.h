#ifndef POSITION_MANAGER_UP__H
#define POSITION_MANAGER_UP__H

#include "PositionManager.h"

class PositionManager_Up : public PositionManager
{

public:
    std::vector<Position> getFuturePositions(const Box& box) override;
};

#endif
