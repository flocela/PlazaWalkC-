#ifndef RECORDERLISTENER__H
#define RECORDERLISTENER__H

#include <unordered_map>
#include <unordered_set>
#include "Position.h"

class RecorderListener 
{
public:
    virtual void receiveAllPositions(std::unordered_map<int, std::unordered_set<Position>> setOfPositionsPerType) = 0;
};

#endif

