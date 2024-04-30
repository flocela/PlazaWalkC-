#ifndef BOARDLISTENER
#define BOARDLISTENER

#include <unordered_map>
#include <unordered_set>
#include "BoxInfo.h"
#include "Drop.h"

/*
Receives from Board 1) changes to Spots and 2) the current state of the Boxes. Changes to Spots are in the form of an unordered_set<Drop>. changedDrops only contains the Drops that have changed since the last time receiveChanges() was called. The current state of the Boxes is in the form of an unordered_map<int, BoxInfo>, which is the Boxes per their id. All Boxes are included, even Boxes that have not entered the Board yet or have been removed because they reached their final destination.
*/
class BoardListener
{

    public:

    virtual void receiveChanges(std::unordered_set<Drop> changedDrops,
                                std::unordered_map<int, BoxInfo> boxesPerId) = 0;

};

#endif
