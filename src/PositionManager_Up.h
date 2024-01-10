#ifndef POSITION_MANAGER_UP__H
#define POSITION_MANAGER_UP__H

#include "PositionManager.h"

class PositionManager_Up : public PositionManager
{
public:
    PositionManager_Up(int finalY, int smallX, int largeX, int smallY, int largeY);
    PositionManager_Up() = delete;
    PositionManager_Up(const PositionManager_Up& o) = default;
    PositionManager_Up(PositionManager_Up&& o) noexcept = default;
    PositionManager_Up& operator=(const PositionManager_Up& o) = default;
    PositionManager_Up& operator=(PositionManager_Up&& o) noexcept = default;
    ~PositionManager_Up() = default;

    std::vector<Position> getFuturePositions(const Box& box) override;
    bool atEnd(const Box& box) override;

private:
    int _endY;
    int _smallX;
    int _largeX;
    int _smallY;
    int _largeY;
};

#endif
