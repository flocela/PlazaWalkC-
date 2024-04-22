#include <utility>
#include "Recorder.h"
#include <iostream>

using namespace std;

Recorder::Recorder()
{
    _dropSetPerType.insert({SpotType::to_arrive, unordered_set<Drop>{}});
    _dropSetPerType.insert({SpotType::arrive, unordered_set<Drop>{}});
    _dropSetPerType.insert({SpotType::to_leave, unordered_set<Drop>{}});
    _dropSetPerType.insert({SpotType::left, unordered_set<Drop>{}});
}

void Recorder::receiveChanges(
        std::unordered_map<SpotType, unordered_set<Drop>> setOfChangedDropsPerType,
        std::unordered_map<int, BoxInfo> boxes)
{
    // The incoming sets of drops are divided per SpotType, setOfChangedDropsPerType.
    // Recorder contains a map of set of drops divided per SpotType, _dropSetPerType.
    // If an incoming drop is in the wrong set in _dropSetPerType, remove it from 
    // the set, and add it to the correct set.
    for (const auto& incomingSetPerType : setOfChangedDropsPerType)
    {
        const SpotType& incomingType = incomingSetPerType.first;
        const unordered_set<Drop>& incomingDrops = incomingSetPerType.second; 

        for (const auto& drop : incomingDrops)
        {   
            for (const auto& dropSetPerType : _dropSetPerType)
            {
                const SpotType& curType = dropSetPerType.first;

                if (_dropSetPerType.at(curType).find(drop) != _dropSetPerType.at(curType).end())
                {
                    _dropSetPerType.at(curType).erase(drop);
                    break; 
                }
            }

            // Add the incoming drop to its corresponding set of drops.
            if (incomingType != SpotType::left)
            {
                _dropSetPerType[incomingType].insert(drop);
            }
        }
    }
    
    for (RecorderListener* listener : _listeners)
    {
        listener->receiveAllDrops(_dropSetPerType, boxes);
    }
}

unordered_map<SpotType, unordered_set<Drop>> Recorder::getDrops()
{
    return _dropSetPerType;
}

void Recorder::registerListener(RecorderListener* listener)
{
    _listeners.push_back(listener);
}
        
