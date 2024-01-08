#ifndef POSITION_MANAGER_UP__H
#define POSITION_MANAGER_UP__H

#include "PositionManager.h"

class PositionManager_Up : public PositionManager
{
public:
    PositionManager_Up(Position finalPosition);
    PositionManager_Up() = delete;
    PositionManager_Up(const PositionManager_Up& o) = default;
    PositionManager_Up(PositionManager_Up&& o) noexcept = default;
    PositionManager_Up& operator=(const PositionManager_Up& o) = default;
    PositionManager_Up& operator=(PositionManager_Up&& o) noexcept = default;
    ~PositionManager_Up() = default;

    std::vector<Position> getFuturePositions(const Box& box) override;
    bool atEnd(const Box& box) override;

private:
    Position _endPosition;
};

#endif
