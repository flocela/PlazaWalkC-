#include "PositionManager_Down.h"

using namespace std;

PositionManager_Down::PositionManager_Down(int finalY, int smallX, int largeX, int smallY, int largeY)
: _endY{finalY},
  _smallX{smallX},
  _largeX{largeX},
  _smallY{smallY},
  _largeY{largeY}
{}

vector<Position> PositionManager_Down::getFuturePositions(const Box& box)
{
    Position curPosition = box.getPosition();

    vector<Position> newPositions{};

    if (curPosition.getY() >= _endY)
    {
        return newPositions;
    }
          
    vector<Position> tempPositions{
        Position{curPosition.getX(), curPosition.getY()+1},
        Position{curPosition.getX()-1, curPosition.getY()+1},
        Position{curPosition.getX()+1, curPosition.getY()+1}};

    for (Position pos : tempPositions)
    {
        if (pos.getY() <= _endY &&
            pos.getY() >= _smallY &&
            pos.getY() <= _largeY &&
            pos.getX() >= _smallX &&
            pos.getX() <= _largeX)
        {
            newPositions.push_back(pos);
        }
    }

    return newPositions;
}    
     
bool PositionManager_Down::atEnd(const Box& box)
{
    return box.getPosition().getY() == _endY;
}
