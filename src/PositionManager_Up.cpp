#include "PositionManager_Up.h"

using namespace std;

PositionManager_Up::PositionManager_Up(int finalY, int smallX, int largeX, int smallY, int largeY)
: _endY{finalY},
  _smallX{smallX},
  _largeX{largeX},
  _smallY{smallY},
  _largeY{largeY}
{}

vector<Position> PositionManager_Up::getFuturePositions(const Box& box)
{
    Position curPosition = box.getPos(std::chrono::high_resolution_clock::now());

    vector<Position> newPositions{};

    if (curPosition.getY() <= _endY)
    {
        return newPositions;
    }
          
    vector<Position> tempPositions{
        Position{curPosition.getX(), curPosition.getY()-1},
        Position{curPosition.getX()+1, curPosition.getY()-1},
        Position{curPosition.getX()-1, curPosition.getY()-1}};

    for (Position pos : tempPositions)
    {
        if (pos.getY() >= _endY &&
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

bool PositionManager_Up::atEnd(const Box& box)
{
    return box.getPos(std::chrono::high_resolution_clock::now()).getY() == _endY;
}
    
    
