#include "Mover_Up.h"

using namespace std;

vector<Position> Mover_Up::getFuturePositions(const Box& box)
{
    Position curPosition = box.getPos(std::chrono::high_resolution_clock::now());
    vector<Position> newPositions{
        Position{curPosition.getX(), curPosition.getY()-1},
        Position{curPosition.getX()+1, curPosition.getY()-1},
        Position{curPosition.getX()-1, curPosition.getY()-1}
    };
    
    return newPositions;
}
