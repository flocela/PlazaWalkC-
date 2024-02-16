#ifndef BOARDLISTENER
#define BOARDLISTENER

#include <unordered_map>
#include <unordered_set>
#include "Drop.h"

class BoardListener
{

public:

    virtual void receiveChanges(std::unordered_map<int, std::unordered_set<Drop>> setsOfDropsPerType) = 0;

};

#endif
