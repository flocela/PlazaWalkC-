#include <utility>
#include "Recorder.h"
#include <iostream>

using namespace std;

Recorder::Recorder()
{}

void Recorder::receiveChanges(
        unordered_set<Drop> changedDrops,
        std::unordered_map<int, BoxInfo> boxes)
{
    for (const auto& drop: changedDrops)
    {
        // If a Drop with drop's Position exists in _drops, then delete the Drop in _drops.
        if (_drops.find(drop) != _drops.end())
        {
            _drops.erase(drop);
        }

        // If drop is not SpotType::left, then save it in _drops.
        if(drop.getSpotType() != SpotType::left)
        {   
            _drops.insert(drop);
        }
    }
    
    for (RecorderListener* listener : _listeners)
    {
        listener->receiveAllDropsAllBoxes(_drops, boxes);
    }
}

void Recorder::registerListener(RecorderListener* listener)
{
    _listeners.push_back(listener);
}
        
