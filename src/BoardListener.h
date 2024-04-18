#ifndef BOARDLISTENER
#define BOARDLISTENER

#include <unordered_map>
#include <unordered_set>
#include "BoxInfo.h"
#include "Drop.h"
#include "SpotType.h"

class BoardListener
{

public:

    virtual void receiveChanges(std::unordered_map<SpotType,std::unordered_set<Drop>> setsOfDropsPerType,
                                std::unordered_map<int, BoxInfo> boxes) = 0;

};

#endif
