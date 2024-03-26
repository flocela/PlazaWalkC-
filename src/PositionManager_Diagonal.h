#ifndef POSITIONMANAGER_DIAGONAL__H
#define POSITIONMANAGER_DIAGONAL__H

#include "Position.h"
#include "PositionManager.h"

class PositionManager_Diagonal : public PositionManager
{

public:
    PositionManager_Diagonal(
        Position topLeft,
        Position botRight,
        int boardMinX,
        int boardMaxX,
        int boardMinY,
        int boardMaxY);

    PositionManager_Diagonal() = delete;
    PositionManager_Diagonal(const PositionManager_Diagonal& o) = default;
    PositionManager_Diagonal(PositionManager_Diagonal&& o) noexcept = default;
    PositionManager_Diagonal& operator= (const PositionManager_Diagonal& o) = default;
    PositionManager_Diagonal& operator= (PositionManager_Diagonal&& o) = default;

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
    double getDistSquared(Position a, Position b);
}; 

#endif
