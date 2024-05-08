#ifndef POSITIONMANAGER_DIAGONAL__H
#define POSITIONMANAGER_DIAGONAL__H

#include "PositionManager.h"

/*
Evaluates all Positions adjacent to the Box's current Position and suggests the closest Position to the target Positon. This results in the Box moving diagonally until it is parallel to the target Position. Then it moves horizontally or vertically to reach the target Position.
*/
class PositionManager_Diagonal : public PositionManager
{

    public:

    /*
    @endRectangle is the Rectangle at which point atEnd() returns true. @targetPosition is the Position PositionManager_Diagonal targets, this is the target destination.
    */ 
    PositionManager_Diagonal(
        Rectangle endRectangle,
        Position targetPosition,
        int boardMinX,
        int boardMaxX,
        int boardMinY,
        int boardMaxY);

    PositionManager_Diagonal() = delete;
    PositionManager_Diagonal(const PositionManager_Diagonal& o) = default;
    PositionManager_Diagonal(PositionManager_Diagonal&& o) noexcept = default;
    PositionManager_Diagonal& operator= (const PositionManager_Diagonal& o) = default;
    PositionManager_Diagonal& operator= (PositionManager_Diagonal&& o) = default;

    /* 
     Collects the all Positions adjacent to @position in a vector. Then sorts the vector by shortest distance to targetPosition. Then shuffles Positions after index 2. The resulting vector will have the first 3 Positions in order by shortest distance to the target Position. The rest of the  Positions will be in a random order. If @position is at targetPosition, then returns an empty vector.
    */
    std::vector<Position> getFuturePositions(Position position) override;

    
    /*
    If @position is within the topLeft corner and botRight corner of the end rectangle given in the constructor, then returns true.  Otherwise returns false. 'Within' means inclusively in the x and y ranges of the end rectangle's top left and bottom right corners.
    */
    bool atEnd(Position position) const override;


    /*
    Returns the end Rectangle.
    */
    Rectangle getEndRect() const override;


    /*
    Returns the target position as a Rectangle. Both of the target Rectangle's top left and bottom right corners are the target Position. This results in the the returned Rectangle having a height and width of zero.
    */
    Rectangle getTargetRect() const override;


    private:

    Rectangle _endRectangle;

    Position _targetPosition;

    int _boardMinX = 0;
    int _boardMaxX = 0;
    int _boardMinY = 0;
    int _boardMaxY = 0;

    std::vector<std::pair<int, int>> pastPositions{};
    double getDistSquared(Position a, Position b);
    bool isValid(Position& p) const;
}; 

#endif
