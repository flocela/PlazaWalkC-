#ifndef POSITIONMANAGER_STEP__H 
#define POSITIONMANAGER_STEP__H

#include <vector>
#include "Position.h"
#include "PositionManager.h"

/*
Suggested movement looks like steps along a line from the start position to finalTarget.
*/
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

    /*
    Note that past calls to getFuturePositions() affect the current call to getFuturePositions().

    When getFuturePosition() is called, the current target is set if there is no current target or if @position is at the current target. To set the current target, a line is drawn from @position to the finalTarget. Travel either one unit in the x or y direction along the line from @position to the final target. Choose to travel one unit in the direction that is closest to the final target. So if the @position is {0, 0} and the final target is at {2, 6}, then choose Position{1, 3} as the current target Position. If the current target is set and @position is not at the current target, then the current target is used.
m

    A vector of adjacent Positions from @position is made and sorted by closest to the current target. The Positions at index 3 and above (if index 3 exists) are shuffled. It may be that the vector only has 3 Positions because there are only 3 valid adjacent Positions to @position (@position could be at a corner).

    If @position is at finalTarget, then returns an empty vector.
    */
    std::vector<Position> getFuturePositions(Position position) override;

    /*
    Returns true if @position is the finalTarget.
    */
    bool atEnd(Position position) const override;

    /*
    Returns a Rectangle where the top left and bottom right corners are the same Position, the final target Position.
    */
    Rectangle getEndRect() const override;

    /*
    Returns a Rectangle where the top left and bottom right corners are the same Position, the final target Position.
    */
    Rectangle getTargetRect() const override;

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
    
