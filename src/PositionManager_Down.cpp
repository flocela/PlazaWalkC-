#include "PositionManager_Down.h"

using namespace std;

vector<Position> PositionManager_Down::getFuturePositions(const Box& box)
{
    Position curPosition = box.getPos(std::chrono::high_resolution_clock::now());
    
    vector<Position> newPositions{
        Position{curPosition.getX(), curPosition.getY()+1},
        Position{curPosition.getX()-1, curPosition.getY()+1},
        Position{curPosition.getX()+1, curPosition.getY()+1}};

    return newPositions;
}    
            
     
