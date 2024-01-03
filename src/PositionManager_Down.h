#ifndef POSITION_MANAGER_DOWN__H
#define POSITION_MANAGER_DOWN__H

#include "PositionManager.h"

class PositionManager_Down : public PositionManager 
{

public:
    std::vector<Position> getFuturePositions(const Box& box) override;
};

#endif
    
