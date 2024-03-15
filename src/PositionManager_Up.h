#ifndef POSITION_MANAGER_UP__H
#define POSITION_MANAGER_UP__H

#include "PositionManager.h"

class PositionManager_Up : public PositionManager
{
public:
    PositionManager_Up(int finalY, int boardMinX, int boardMaxX, int boardMinY, int boardMaxY);
    PositionManager_Up() = delete;
    PositionManager_Up(const PositionManager_Up& o) = default;
    PositionManager_Up(PositionManager_Up&& o) noexcept = default;
    PositionManager_Up& operator=(const PositionManager_Up& o) = default;
    PositionManager_Up& operator=(PositionManager_Up&& o) noexcept = default;
    ~PositionManager_Up() = default;

    std::vector<Position> getFuturePositions(Position position) override;
    bool atEnd(Position position) override;
    std::pair<Position, Position> getEndPoint() const override;

private:
    int _endY;
    int _boardMinX;
    int _boardMaxX;
    int _boardMinY;
    int _boardMaxY;
};

#endif
