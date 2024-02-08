#include <utility>
#include "Recorder.h"

using namespace std;

void Recorder::receiveChanges(std::unordered_map<Position, int>& typePerPosition)
{ 
    // _positionSetsPerType is a map of sets per type. Remove position from former set (if it is contained in a former set). Add position to corresponding set. 
    for (const auto& pairTypePerPosition : typePerPosition)
    {
        Position givenPosition = pairTypePerPosition.first;
        int givenType = pairTypePerPosition.second;

        // iterate through each type in _positionSetsPerType 
        for (const auto& pairPositionSetPerType : _positionSetsPerType)
        {
            int recordedType = pairPositionSetPerType.first;
            if (_positionSetsPerType.at(recordedType).find(givenPosition) != _positionSetsPerType.at(recordedType).end())
            {
                if (recordedType != givenType)
                {
                    _positionSetsPerType.at(recordedType).erase(givenPosition);
                }
                
            }
            if (givenType == recordedType && givenType != -1)
            {
                _positionSetsPerType.at(recordedType).insert(givenPosition);
            }
        }
    }
}

unordered_map<int, unordered_set<Position>> Recorder::getPositions()
{
    return unordered_map<int, unordered_set<Position>>{};
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

        
            
        

        
