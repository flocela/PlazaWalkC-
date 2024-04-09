#ifndef POSITIONMANAGER_SLIDE__H 
#define POSITIONMANAGER_SLIDE__H

#include <vector>
#include "Position.h"
#include "PositionManager.h"

class PositionManager_Slide : public PositionManager
{
public:
  
    PositionManager_Slide( 
        Position finalTarget,
        int boardMinX,
        int boardMaxX,
        int boardMinY,
        int boardMaxY);

    PositionManager_Slide() = delete;
    PositionManager_Slide(const PositionManager_Slide& o) = default;
    PositionManager_Slide(PositionManager_Slide&& o) noexcept = default;
    PositionManager_Slide& operator=(const PositionManager_Slide& o) = default;
    PositionManager_Slide& operator=(PositionManager_Slide&& o) noexcept = default;

    std::vector<Position> getFuturePositions(Position position) override;
    bool atEnd(Position position) override;
    std::pair<Position, Position> getEndPoint() const override;
    

private:
   
    Position _finalTarget;
    Position _curTarget = Position{-1, -1};
    
    int _boardMinX = 0;
    int _boardMaxX = 0;
    int _boardMinY = 0;
    int _boardMaxY = 0;

    void setCurrentTarget(Position curPosition);
    double getDistSquared(Position a, Position b) const;
};

#endif
    
