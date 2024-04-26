#include <utility>
#include "Recorder.h"
#include <iostream>

using namespace std;

Recorder::Recorder()
{}

// Receives changes to Drops and current state of Boxes and broadcasts the current state of all the Drops and Boxes.
// Since it only receives changes to Drops, it must keeping a running state of all the Drops and add the changes as they are received.
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
        
