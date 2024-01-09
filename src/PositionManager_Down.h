#ifndef POSITION_MANAGER_DOWN__H
#define POSITION_MANAGER_DOWN__H

#include "PositionManager.h"

class PositionManager_Down : public PositionManager 
{

public:
    PositionManager_Down(int finalY, int smallX, int largeX, int smallY, int largeY);
    PositionManager_Down() = delete;
    PositionManager_Down(const PositionManager_Down& o) = default;
    PositionManager_Down(PositionManager_Down&& o) noexcept = default;
    PositionManager_Down& operator=(const PositionManager_Down& o) = default;
    PositionManager_Down& operator=(PositionManager_Down&& o) noexcept = default;
    ~PositionManager_Down() = default;

    std::vector<Position> getFuturePositions(const Box& box) override;
    bool atEnd(const Box& box) override;

private:
    int _endY;

    // edges of the board
    int _smallX = 0;
    int _largeX = 0;
    int _smallY = 0;
    int _largeY = 0;
};

#endif
    
