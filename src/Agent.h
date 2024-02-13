#ifndef AGENT__H
#define AGENT__H

#include <unordered_map>
#include "Position.h"

class Agent
{
public:
    virtual void updateWithChanges() = 0;

    virtual void receiveChanges(std::unordered_map<Position, int> typePerPosition) = 0;
};

#endif
