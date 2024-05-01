#include "PositionManager_Diagonal.h"
#include <algorithm>
#include <iterator>
#include <random>

using namespace std;

PositionManager_Diagonal::PositionManager_Diagonal(
    Rectangle destinationRectangle,
    int boardMinX,
    int boardMaxX,
    int boardMinY,
    int boardMaxY)
  : _topLeftX{destinationRectangle.getTopLeft().getX()},
    _topLeftY{destinationRectangle.getTopLeft().getY()},
    _botRightX{destinationRectangle.getBottomRight().getX()},
    _botRightY{destinationRectangle.getBottomRight().getY()},
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

    // Collect all possible new Positions, in all 8 directions.
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

    // Calculate distance to each of the new Positions.
    pairsOfPositionsAndDistSq.push_back({getDistSquared(n, target), n}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(nw, target), nw}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(w, target), w}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(sw, target), sw}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(s, target), s}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(se, target), se}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(e, target), e}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(ne, target), ne}); 
   
    // Remove Positions that are outside of the Board. 
    vector<pair<double,Position>> netPositionPairs{};
    for (const auto& p: pairsOfPositionsAndDistSq)
    {
        Position pos = p.second;

        if (pos.getX() >= _boardMinX &&
            pos.getX() <= _boardMaxX &&
            pos.getY() >= _boardMinY &&
            pos.getY() <= _boardMaxY)
        {
            netPositionPairs.push_back(p);
        }
    }

    // Sort the vector by closes to center of destination rectangle.
    sort(netPositionPairs.begin(), netPositionPairs.end(), [](const pair<double, Position>& a, const pair<double, Position>& b){return a.first < b.first;});

    random_device rd;
    mt19937 g(rd());

    vector<Position> newPositions{};
    for(const auto& p : netPositionPairs)
    {
        newPositions.push_back(p.second);
    }

    // Shuffle positions after the 3rd position.
    if (newPositions.size() > 3)
    {
        shuffle(newPositions.begin()+3, newPositions.end(), g);
    }

    return newPositions;
    
}

double PositionManager_Diagonal::getDistSquared(Position a, Position b)
{
    double x = std::abs(static_cast<double>(a.getX()) - b.getX());
    double y = std::abs(static_cast<double>(a.getY()) - b.getY());

    return (x * x) + (y * y);
}

// TODO needs a test
Rectangle PositionManager_Diagonal::getEndRect() const
{
    return Rectangle{Position{_topLeftX, _topLeftY}, Position{_botRightX, _botRightY}};
}

bool PositionManager_Diagonal::isValid(Position& p) const
{
    return  (p.getX() >= _boardMinX &&
             p.getX() <= _boardMaxX &&
             p.getY() >= _boardMinY &&
             p.getY() <= _boardMaxY);
}

string PositionManager_Diagonal::invalidPositionErrorString(Position p) const
{
    return  p.toString() + " is an invalid Position.";
}
