#include <utility>
#include "Recorder.h"
#include <iostream>

using namespace std;

Recorder::Recorder()
{
    for (int ii=1; ii<=4; ++ii)
    {
        _dropSetsPerType.insert({ii, unordered_set<Drop>{}});
    }        
}

void Recorder::receiveChanges(std::unordered_map<int, unordered_set<Drop>> changedSetsOfDropsPerType)
{ 
    // _positionSetsPerType is a map of sets per type.
    // It may be that position needs to be moved from one type's set to another type's set.

    // Remove position from former set (if it is contained in a former set).
    // And add position to its new set. 

    int receivedcount = 0;
    for (const auto& setOfDropsPerType : changedSetsOfDropsPerType)
    {
        receivedcount += setOfDropsPerType.second.size();
    }

    cout << "Recorder receivecCount: " << receivedcount << endl;
    


    for (const auto& changedSetPerType : changedSetsOfDropsPerType)
    {
        
        int newType = changedSetPerType.first;

        for (const auto& drop : changedSetPerType.second)
        {
            int eraseCount = 0; 
            // for each set in _positionsetsPerType 
            for (const auto& dropSetPerType : _dropSetsPerType)
            {
                int curType = dropSetPerType.first;

                if (_dropSetsPerType.at(curType).find(drop) != _dropSetsPerType.at(curType).end())
                {
                    _dropSetsPerType.at(curType).erase(drop);
                    ++eraseCount;
                    break; 
                }
            }
            cout << "eraseCount: " << eraseCount << endl;

            if (newType != -1)
            {
                _dropSetsPerType[newType].insert(drop);
            }
        }
    }

    int count = 0;
    for (const auto& dropSetPerType : _dropSetsPerType)
    {
        count += dropSetPerType.second.size();
    }
    cout << "Recorder num of drops in dropSetsPerType: " << count << endl;
    
    for (RecorderListener* listener : _listeners)
    {
        listener->receiveAllDrops(_dropSetsPerType);
    }
}

unordered_map<int, unordered_set<Drop>> Recorder::getDrops()
{
    return unordered_map<int, unordered_set<Drop>>{};
}

void Recorder::registerListener(RecorderListener* listener)
{
    _listeners.push_back(listener);
}

   /* 
    
    BoardNote boardNote = board.getNoteAt(position);

    if (boardNote.getType() != -1)
    {
        //SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }

    // create square with width 10.
    SDL_Rect squareRect;
    squareRect.w = 10;
    squareRect.h = 10;
    squareRect.x = position.getX();
    squareRect.y = position.getY();

    //SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(_renderer, &squareRect);

    SDL_RenderPresent(_renderer);
*/

        
            
        

        
