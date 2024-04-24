#ifndef POSITION_MANAGER_DOWN__H
#define POSITION_MANAGER_DOWN__H

#include "PositionManager.h"

class PositionManager_Down : public PositionManager 
{

    public:

    // PositionManager's destination is a horizontal line at finalY.
    PositionManager_Down(int finalY, int boardMinX, int boardMaxX, int boardMinY, int boardMaxY);
    PositionManager_Down() = delete;
    PositionManager_Down(const PositionManager_Down& o) = default;
    PositionManager_Down(PositionManager_Down&& o) noexcept = default;
    PositionManager_Down& operator=(const PositionManager_Down& o) = default;
    PositionManager_Down& operator=(PositionManager_Down&& o) noexcept = default;
    ~PositionManager_Down() = default;

    // Returns a vector of three Positions. Say position's x-value is x and y-value is y. Then the Positions will be {{Position{x, y+/-1}, Position{x-1, y}, Position{x+1, y}}. The first Position moves the box closer to the end line. The second and third Positions move horizontally paralledl to the end line. Positions that are not on the Board, are deleted from the returned vector.
    std::vector<Position> getFuturePositions(Position position) override;

    bool atEnd(Position position) override;

    std::pair<Position, Position> getEndPoint() const override;

    private:

    int _endY;

    // edges of the board
    int _boardMinX = 0;
    int _boardMaxX = 0;
    int _boardMinY = 0;
    int _boardMaxY = 0;
};

#endif
    
