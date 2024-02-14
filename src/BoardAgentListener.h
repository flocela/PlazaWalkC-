#ifndef BOARDAGENTLISTENER
#define BOARDAGENTLISTENER

#include <unordered_map>
#include "Position.h"

class BoardAgentListener
{

public:

    virtual void receiveChanges(std::unordered_map<Position, int> typesPerPosition) = 0;

};

#endif
