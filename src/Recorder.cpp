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
        if (_drops.find(drop) != _drops.end())
        {
            _drops.erase(drop);
        }
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
        
