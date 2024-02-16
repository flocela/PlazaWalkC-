#ifndef AGENT__H
#define AGENT__H

#include <unordered_map>
#include "Position.h"

class Agent
{
public:
    virtual void updateWithChanges() = 0;
};

#endif
