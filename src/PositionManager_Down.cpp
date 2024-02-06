#include "PositionManager_Down.h"

using namespace std;

PositionManager_Down::PositionManager_Down(int finalY, int boardMinX, int boardMaxX, int boardMinY, int boardMaxY)
: _endY{finalY},
  _boardMinX{boardMinX},
  _boardMaxX{boardMaxX},
  _boardMinY{boardMinY},
  _boardMaxY{boardMaxY}
{}

vector<Position> PositionManager_Down::getFuturePositions(Position position)
{
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
        if (pos.getY() <= _endY &&
            pos.getY() >= _boardMinY &&
            pos.getY() <= _boardMaxY &&
            pos.getX() >= _boardMinX &&
            pos.getX() <= _boardMaxX)
        {
            newPositions.push_back(pos);
        }
    }

    return newPositions;
}    
     
bool PositionManager_Down::atEnd(Position position)
{
    return position.getY() == _endY;
}
