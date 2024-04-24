#ifndef POSITIONMANAGER_STEP__H 
#define POSITIONMANAGER_STEP__H

#include <vector>
#include "Position.h"
#include "PositionManager.h"

// Suggested movement looks like steps along a line from the start position
// to the final position.
class PositionManager_Step : public PositionManager
{
public:
  
    PositionManager_Step( 
        Position finalTarget,
        int boardMinX,
        int boardMaxX,
        int boardMinY,
        int boardMaxY);

    PositionManager_Step() = delete;
    PositionManager_Step(const PositionManager_Step& o) = default;
    PositionManager_Step(PositionManager_Step&& o) noexcept = default;
    PositionManager_Step& operator=(const PositionManager_Step& o) = default;
    PositionManager_Step& operator=(PositionManager_Step&& o) noexcept = default;
    ~PositionManager_Step() = default;

    // Note that past calls to getFuturePositions affect the current call to getFuturePositions().
    // When getFuturePositions is called a line is drawn from position to the finalTarget.  Not all points on the line are Positions because Positions are digital. If the current target already exists then it is not updated. If the current target has not been set a new current target is set. If position is at the current target, then a new current target is set. The first Position on the line is set as the current target. A vector of adjacent Positions from position is made and sorted by closest to the current target. The Positions at index 3 and above (if index 3 exists) are shuffled. It may be that the vector only has 3 Positions because there are only 3 valid adjacent Positions to position (position could be at a corner).
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
    bool isValid(Position& p) const;
    std::string invalidPositionErrorString(Position p) const;
};

#endif
    
