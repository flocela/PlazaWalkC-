#include "PositionManager_Up.h"

using namespace std;

PositionManager_Up::PositionManager_Up(Position finalPosition): _endPosition{finalPosition} {}

vector<Position> PositionManager_Up::getFuturePositions(const Box& box)
{
    Position curPosition = box.getPos(std::chrono::high_resolution_clock::now());
    vector<Position> newPositions{
        Position{curPosition.getX(), curPosition.getY()-1},
        Position{curPosition.getX()+1, curPosition.getY()-1},
        Position{curPosition.getX()-1, curPosition.getY()-1}
    };
    
    return newPositions;
}

bool PositionManager_Up::atEnd(const Box& box)
{
    return box.getPos(std::chrono::high_resolution_clock::now()) == _endPosition;
}
    
    
