#include "PositionManager_Diagonal.h"

using namespace std;

PositionManager_Diagonal::PositionManager_Diagonal(
    Position topLeft,
    Position botRight,
    int boardMinX,
    int boardMaxX,
    int boardMinY,
    int boardMaxY)
  : _topLeftX{topLeft.getX()},
    _topLeftY{topLeft.getY()},
    _botRightX{botRight.getX()},
    _botRightY{botRight.getY()},
    _targetX{(_topLeftX + _botRightX)/2},
    _targetY{(_topLeftY + _botRightY)/2},
    _boardMinX{boardMinX},
    _boardMaxX{boardMaxX},
    _boardMinY{boardMinY},
    _boardMaxY{boardMaxY}
{}

bool PositionManager_Diagonal::atEnd(Position position)
{
    return position.getX() >= _topLeftX && position.getX() <= _botRightX &&
           position.getY() >= _topLeftY && position.getY() <= _botRightY;
}

vector<Position> PositionManager_Diagonal::getFuturePositions(Position position)
{
    if (atEnd(position))
    {
        return vector<Position>{};
    }

    int curX = position.getX();
    int curY = position.getY();

    int deltaX = _targetX - position.getX();
    int deltaY = _targetY - position.getY();

    int xDir = (deltaX > 0) ? 1 : -1;
    xDir = (deltaX == 0) ? 0 : xDir;

    int yDir = (deltaY > 0) ? 1 : -1;
    yDir = (deltaY == 0) ? 0 : yDir;

    Position positionA{curX + xDir, curY};
    Position positionB{curX, curY + yDir};
    Position positionC{curX + xDir, curY + yDir};

    double distASquared = getDistSquared(positionA, Position{_targetX, _targetY});
    double distBSquared = getDistSquared(positionB, Position{_targetX, _targetY});
    double distCSquared = getDistSquared(positionC, Position{_targetX, _targetY});

    vector<pair<double, Position>> pairsOfPositionsAndDistSq{};
    pairsOfPositionsAndDistSq.push_back({distASquared, positionA});
    pairsOfPositionsAndDistSq.push_back({distBSquared, positionB});
    pairsOfPositionsAndDistSq.push_back({distCSquared, positionC});

    sort(pairsOfPositionsAndDistSq.begin(), pairsOfPositionsAndDistSq.end(), [](const pair<double, Position>& a, const pair<double, Position>& b){return a.first < b.first;});

    vector<Position> tempPositions{};
    tempPositions.push_back(pairsOfPositionsAndDistSq[0].second);
    if (pairsOfPositionsAndDistSq[1].first == pairsOfPositionsAndDistSq[2].first)
    {
        if(rand()%1)
        {
            tempPositions.push_back(pairsOfPositionsAndDistSq[1].second);
            tempPositions.push_back(pairsOfPositionsAndDistSq[2].second);
        }
        else
        {
            tempPositions.push_back(pairsOfPositionsAndDistSq[2].second);
            tempPositions.push_back(pairsOfPositionsAndDistSq[1].second);
        }
    }
    else
    {
        tempPositions.push_back(pairsOfPositionsAndDistSq[1].second);
        tempPositions.push_back(pairsOfPositionsAndDistSq[2].second);
    }
    // TODO test that there is a fourth position that is random
    if(rand()%1)
    {
        tempPositions.push_back(Position{curX - xDir, curY});
    }
    else
    {
        tempPositions.push_back(Position{curX, curY - yDir});
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

double PositionManager_Diagonal::getDistSquared(Position a, Position b)
{
    double x = std::abs(static_cast<double>(a.getX()) - b.getX());
    double y = std::abs(static_cast<double>(a.getY()) - b.getY());

    return (x * x) + (y * y);
}

    

// TODO needs a test
std::pair<Position, Position> PositionManager_Diagonal::getEndPoint() const
{
    return pair<Position, Position>{Position{_topLeftX, _topLeftY}, Position{_botRightX, _botRightY}};
}
