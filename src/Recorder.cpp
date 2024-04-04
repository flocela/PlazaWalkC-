#include <utility>
#include "Recorder.h"
#include <iostream>

using namespace std;

Recorder::Recorder()
{
    _dropSetsPerType.insert({SpotType::to_arrive, unordered_set<Drop>{}});
    _dropSetsPerType.insert({SpotType::arrive, unordered_set<Drop>{}});
    _dropSetsPerType.insert({SpotType::to_leave, unordered_set<Drop>{}});
    _dropSetsPerType.insert({SpotType::left, unordered_set<Drop>{}});
}

void Recorder::receiveChanges(std::unordered_map<SpotType, unordered_set<Drop>> changedSetsOfDropsPerType, std::unordered_map<int, Box> boxes)
{ 
    // _positionSetsPerType is a map of postion sets per type.
    // It may be that position needs to be moved from one type's set to another type's set.

    // Remove position from former set (if it is contained in a former set).
    // And add position to its new set. 

    for (const auto& changedSetPerType : changedSetsOfDropsPerType)
    {
        
        SpotType newType = changedSetPerType.first;

        for (const auto& drop : changedSetPerType.second)
        {   // TODO make is so this never happens, shouldn't have to check.
            // OR TODO make a test for this exception.
            if (drop._type != newType)
            {
                throw invalid_argument("drop type is different from designated set type.");
            }
            // for each set in _positionsetsPerType 
            for (const auto& dropSetPerType : _dropSetsPerType)
            {
                SpotType curType = dropSetPerType.first;

                if (_dropSetsPerType.at(curType).find(drop) != _dropSetsPerType.at(curType).end())
                {
                    _dropSetsPerType.at(curType).erase(drop);
                    break; 
                }
            }

            if (newType != SpotType::left)
            {
                _dropSetsPerType[newType].insert(drop);
            }
        }
    }
    
    for (RecorderListener* listener : _listeners)
    {
        listener->receiveAllDrops(_dropSetsPerType, boxes);
    }
}

unordered_map<SpotType, unordered_set<Drop>> Recorder::getDrops()
{
    return _dropSetsPerType;
}

void Recorder::registerListener(RecorderListener* listener)
{
    _listeners.push_back(listener);
}
        
