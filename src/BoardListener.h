#ifndef BOARDLISTENER
#define BOARDLISTENER

#include <unordered_map>
#include <unordered_set>
#include "BoxInfo.h"
#include "Drop.h"
#include "SpotType.h"

// Receives 1) changes to Spots from Board and 2) the current state of the Boxes. Changes to Spots are in the form of an unordered_map<SpotType, unordered_set<Drop>>. This map only contains the Spot changes since the last time it received changes. The current state of the Boxes is in the form of an unordered_map<int, BoxInfo>. All Boxes are included, even Boxes that have not entered the Board yet or have been removed because they reached their final destination.
class BoardListener
{

public:

    virtual void receiveChanges(std::unordered_map<SpotType,std::unordered_set<Drop>> setOfChangedDropsPerType,
                                std::unordered_map<int, BoxInfo> boxesPerId) = 0;

};

#endif
