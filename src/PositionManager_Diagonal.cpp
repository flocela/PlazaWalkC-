#include "PositionManager_Diagonal.h"
#include <algorithm>
#include <iterator>
#include <random>
#include <sstream>

#include "Util.h"

using namespace std;

PositionManager_Diagonal::PositionManager_Diagonal(
    Rectangle endRectangle,
    Position targetPosition,
    int boardMinX,
    int boardMaxX,
    int boardMinY,
    int boardMaxY)
  : _endRectangle{endRectangle},
    _targetPosition{targetPosition},
    _boardMinX{boardMinX},
    _boardMaxX{boardMaxX},
    _boardMinY{boardMinY},
    _boardMaxY{boardMaxY}
{
    if (!_endRectangle.isInside(_targetPosition))
    {   
        stringstream ss;
        ss << "Target position " << _targetPosition << " is not within end rectangle " << endRectangle << ". ";    
        throw invalid_argument(ss.str());
    }
}

vector<Position> PositionManager_Diagonal::getFuturePositions(Position position)
{
    if (position == _targetPosition)
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

    // Calculate distance to each of the new Positions.
    pairsOfPositionsAndDistSq.push_back({getDistSquared(n, _targetPosition), n}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(nw, _targetPosition), nw}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(w, _targetPosition), w}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(sw, _targetPosition), sw}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(s, _targetPosition), s}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(se, _targetPosition), se}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(e, _targetPosition), e}); 
    pairsOfPositionsAndDistSq.push_back({getDistSquared(ne, _targetPosition), ne}); 
   
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

    // Sort the vector by closest to _targetPosition.
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

bool PositionManager_Diagonal::atEnd(Position position) const
{
    return _endRectangle.isInside(position);
}

Rectangle PositionManager_Diagonal::getEndRect() const
{
    return _endRectangle;
}

Rectangle PositionManager_Diagonal::getTargetRect() const
{
    return Rectangle{_targetPosition, _targetPosition};
}

double PositionManager_Diagonal::getDistSquared(Position a, Position b)
{
    double x = std::abs(static_cast<double>(a.getX()) - b.getX());
    double y = std::abs(static_cast<double>(a.getY()) - b.getY());

    return (x * x) + (y * y);
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
