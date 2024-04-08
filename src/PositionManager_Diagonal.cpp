#include "PositionManager_Diagonal.h"
#include <algorithm>
#include <iterator>
#include <random>

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

    vector<pair<double, Position>> pairsOfPositionsAndDistSq{};
    Position n  = Position{curX, curY+1};
    Position nw = Position{curX + 1, curY + 1};
    Position w  = Position{curX + 1, curY};
    Position sw = Position{curX + 1, curY - 1};
    Position s  = Position{curX, curY - 1};
    Position se = Position{curX - 1, curY - 1};
    Position e  = Position{curX - 1, curY};
    Position ne = Position{curX - 1, curY + 1};
    Position target = Position{_targetX, _targetY};
    pairsOfPositionsAndDistSq.push_back({getDistSquared(n, target), n}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(nw, target), nw}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(w, target), w}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(sw, target), sw}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(s, target), s}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(se, target), se}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(e, target), e}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(ne, target), ne}); 

    sort(pairsOfPositionsAndDistSq.begin(), pairsOfPositionsAndDistSq.end(), [](const pair<double, Position>& a, const pair<double, Position>& b){return a.first < b.first;});

    vector<Position> netPositions{};
    for (const auto& p: pairsOfPositionsAndDistSq)
    {
        Position pos = p.second;

        if (pos.getX() >= _boardMinX &&
            pos.getX() <= _boardMaxX &&
            pos.getY() >= _boardMinY &&
            pos.getY() <= _boardMaxY)
        {
            netPositions.push_back(pos);
        }
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(netPositions.begin()+3, netPositions.end(), g);

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
