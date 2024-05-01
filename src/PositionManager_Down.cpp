#include "PositionManager_Down.h"

using namespace std;

PositionManager_Down::PositionManager_Down(
    int finalY,
    int boardMinX,
    int boardMaxX,
    int boardMinY,
    int boardMaxY)
:   _endY{finalY},
    _boardMinX{boardMinX},
    _boardMaxX{boardMaxX},
    _boardMinY{boardMinY},
    _boardMaxY{boardMaxY}
{}

vector<Position> PositionManager_Down::getFuturePositions(Position position)
{
    if (!isValid(position))
    {
       throw invalid_argument(invalidPositionErrorString(position));
    }    

    Position curPosition = position;

    vector<Position> newPositions{};

    if (curPosition.getY() >= _endY)
    {
        return newPositions;
    }
          
    vector<Position> tempPositions{
        Position{curPosition.getX(), curPosition.getY()+1},
        Position{curPosition.getX()-1, curPosition.getY()},
        Position{curPosition.getX()+1, curPosition.getY()}};

    for (Position pos : tempPositions)
    {
        if (isValid(pos))
        {
            newPositions.push_back(pos);
        }
    }

    return newPositions;
}    
     
bool PositionManager_Down::atEnd(Position position)
{   
    return position.getY() >= _endY;
}

Rectangle PositionManager_Down::getEndRect() const
{
    return Rectangle{Position{_boardMinX, _endY}, Position{_boardMaxX, _endY}};
}
    
bool PositionManager_Down::isValid(Position& p) const
{
    return  (p.getX() >= _boardMinX &&
             p.getX() <= _boardMaxX &&
             p.getY() >= _boardMinY &&
             p.getY() <= _boardMaxY);
}

string PositionManager_Down::invalidPositionErrorString(Position p) const
{
    return  p.toString() + " is an invalid Position.";
}
