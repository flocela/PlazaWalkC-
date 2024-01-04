#ifndef DECIDER__H
#define DECIDER__H

class Decider
{

public:
    virtual Position getNextPosition(vector<Position> possiblePositions) = 0;

}

#endif
