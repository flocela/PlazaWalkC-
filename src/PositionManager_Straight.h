#ifndef POSITIONMANAGER_STRAIGHT__H
#define POSITIONMANAGER_STRAIGHT__H

#include "Position.h"
#include "PositionManager.h"

class PositionManager_Straight : public PositionManager
{

public:
    PositionManager_Straight(
        Position topLeft,
        Position botRight,
        int boardMinX,
        int boardMaxX,
        int boardMinY,
        int boardMaxY);

    PositionManager_Straight() = delete;
    PositionManager_Straight(const PositionManager_Straight& o) = default;
    PositionManager_Straight(PositionManager_Straight&& o) noexcept = default;
    PositionManager_Straight& operator= (const PositionManager_Straight& o) = default;
    PositionManager_Straight& operator= (PositionManager_Straight&& o) = default;
    ~PositionManager_Straight() = default;

    std::vector<Position> getFuturePositions(Position position) override;
    bool atEnd(Position position) override;
    std::pair<Position, Position> getEndPoint() const override;

private:
    int _topLeftX = 0;
    int _topLeftY = 0;
    int _botRightX = 0;
    int _botRightY = 0;

    int _targetX = 0;
    int _targetY = 0;

    int _boardMinX = 0;
    int _boardMaxX = 0;
    int _boardMinY = 0;
    int _boardMaxY = 0;

    std::vector<std::pair<int, int>> pastPositions{};
}; 

#endif
