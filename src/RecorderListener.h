#ifndef RECORDERLISTENER__H
#define RECORDERLISTENER__H

#include <unordered_map>
#include <unordered_set>
#include "BoxInfo.h"
#include "Drop.h"

class RecorderListener 
{
public:
    virtual void receiveAllDrops(std::unordered_map<SpotType, std::unordered_set<Drop>> setOfDropsPerType, std::unordered_map<int, BoxInfo> boxes) = 0;
};

#endif

