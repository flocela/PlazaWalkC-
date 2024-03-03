#include "PositionManager_Straight.h"

using namespace std;

PositionManager_Straight::PositionManager_Straight(
    Position topLeft,
    Position botRight,
    int boardMinX,
    int boardMaxX,
    int boardMinY,
    int boardMaxY)
  : _topLeftX{topLeft.getX()},
    _topLeftY{topLeft.getY()},
    _botRightX{botRight.getY()},
    _botRightY{botRight.getY()},
    _targetX{(_topLeftX + _botRightX)/2},
    _targetY{(_topLeftY + _botRightY)/2},
    _boardMinX{boardMinX},
    _boardMaxX{boardMaxX},
    _boardMinY{boardMinY},
    _boardMaxY{boardMaxY}
{}

bool PositionManager_Straight::atEnd(Position position)
{
    return position.getX() >= _topLeftX && position.getX() <= _botRightX &&
           position.getY() >= _topLeftY && position.getY() <= _botRightY;
}

vector<Position> PositionManager_Straight::getFuturePositions(Position position)
{
    if (atEnd(position))
    {
        return vector<Position>{};
    }

    int deltaY = _targetY - position.getY();
    int deltaX = _targetX - position.getX();

    int xDir = (deltaX > 0) ? 1 : -1;
    xDir = (deltaX == 0) ? 0 : xDir;
    int yDir = (deltaY > 0) ? 1 : -1;
    yDir = (deltaY == 0) ? 0 : yDir;

    double deltaYDist = (( deltaY - yDir) * (deltaY - yDir)) + (deltaX * deltaX);
    double deltaXDist = (deltaY * deltaY) + ((deltaX - xDir) * (deltaX - xDir));

    vector<Position> tempPositions{};
    if (deltaYDist > deltaXDist)
    {
        tempPositions.push_back(Position{position.getX()+xDir, position.getY()});
        tempPositions.push_back(Position{position.getX(), position.getY() + yDir});
        tempPositions.push_back(Position{position.getX(), position.getY()-yDir});
        tempPositions.push_back(Position{position.getX()-xDir, position.getY()});
    }
    else 
    {
        tempPositions.push_back(Position{position.getX(), position.getY() + yDir});
        tempPositions.push_back(Position{position.getX()+xDir, position.getY()});
        tempPositions.push_back(Position{position.getX()-xDir, position.getY()});
        tempPositions.push_back(Position{position.getX(), position.getY()+yDir});
    }

    vector<Position> netPositions{};
    for (Position pos : tempPositions)
    {
        if (pos.getX() >= _boardMinX &&
            pos.getX() <= _boardMaxX &&
            pos.getY() >= _boardMinY &&
            pos.getY() <= _boardMaxY)
        {
            netPositions.push_back(pos);
        }
    }

    return netPositions;
    
}
