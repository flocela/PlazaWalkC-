#include <utility>
#include "Recorder.h"
#include <iostream>

using namespace std;

Recorder::Recorder()
{
    for (int ii=1; ii<=4; ++ii)
    {
        _positionsetsPerType.insert({ii, unordered_set<Position>{}});
    }        
}

void Recorder::receiveChanges(std::unordered_map<Position, int> typesPerPosition)
{ 
    cout << "Recorder.cpp receiveChanges" << endl;
    cout << "Recorder typesPerPosition size: " << typesPerPosition.size() << endl;
    // _positionSetsPerType is a map of sets per type.
    // It may be that position needs to be moved from one type set to another type set.
    // Remove position from former set (if it is contained in a former set).
    // And add position to its new set. 
    for (const auto& typePerPosition : typesPerPosition)
    {
        Position givenPosition = typePerPosition.first;
        int givenType          = typePerPosition.second;

        // iterate through each type in _positionsetsPerType 
        for (const auto& positionsetPerType : _positionsetsPerType)
        {
            int curType = positionsetPerType.first;
            cout <<"Recorder: curType " << curType << endl;

            // find set corresponding to curType. 
            if (_positionsetsPerType.at(curType).find(givenPosition) != _positionsetsPerType.at(curType).end())
            {
                // if curType is not the given type, then delete position from curType's set.
                if (curType != givenType)
                {
                    _positionsetsPerType.at(curType).erase(givenPosition);
                }
                
            }
            
            // if the givenType == curType then add givenPosition to the curType's set. 
            if (givenType == curType)
            {
                _positionsetsPerType.at(curType).insert(givenPosition);
            }
        }
    }
    
    for (RecorderListener* listener : _listeners)
    {
        listener->receiveAllPositions(_positionsetsPerType);
    }
}

unordered_map<int, unordered_set<Position>> Recorder::getPositions()
{
    return unordered_map<int, unordered_set<Position>>{};
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

        
            
        

        
