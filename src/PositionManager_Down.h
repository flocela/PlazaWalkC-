#ifndef POSITION_MANAGER_DOWN__H
#define POSITION_MANAGER_DOWN__H

#include "PositionManager.h"

class PositionManager_Down : public PositionManager 
{

public:
    PositionManager_Down(int finalY, int boardMinX, int boardMaxX, int boardMinY, int boardMaxY);
    PositionManager_Down() = delete;
    PositionManager_Down(const PositionManager_Down& o) = default;
    PositionManager_Down(PositionManager_Down&& o) noexcept = default;
    PositionManager_Down& operator=(const PositionManager_Down& o) = default;
    PositionManager_Down& operator=(PositionManager_Down&& o) noexcept = default;
    ~PositionManager_Down() = default;

    std::vector<Position> getFuturePositions(Position position) override;
    bool atEnd(Position position) override;

private:
    int _endY;

    // edges of the board
    int _boardMinX = 0;
    int _boardMaxX = 0;
    int _boardMinY = 0;
    int _boardMaxY = 0;
};

#endif
    
