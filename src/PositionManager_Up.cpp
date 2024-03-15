#include "PositionManager_Up.h"

using namespace std;

PositionManager_Up::PositionManager_Up(int finalY, int boardMinX, int boardMaxX, int boardMinY, int boardMaxY)
: _endY{finalY},
  _boardMinX{boardMinX},
  _boardMaxX{boardMaxX},
  _boardMinY{boardMinY},
  _boardMaxY{boardMaxY}
{}

vector<Position> PositionManager_Up::getFuturePositions(Position position)
{
    Position curPosition = position;

    vector<Position> newPositions{};

    if (curPosition.getY() <= _endY)
    {
        return newPositions;
    }
          
    vector<Position> tempPositions{
        Position{curPosition.getX(), curPosition.getY()-1},
        Position{curPosition.getX()+1, curPosition.getY()},
        Position{curPosition.getX()-1, curPosition.getY()}
    };

    for (Position pos : tempPositions)
    {
        if (pos.getY() >= _endY &&
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

bool PositionManager_Up::atEnd(Position position)
{
    return position.getY() <= _endY;
}
    
// TODO fill this in later    
std::pair<Position, Position> PositionManager_Up::getEndPoint() const
{
    return pair<Position, Position>{Position{0,0}, Position{0,0}};
}
