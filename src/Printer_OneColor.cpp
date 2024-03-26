#include "Printer_OneColor.h"
#include <iostream>

using namespace std;

Printer_OneColor::Printer_OneColor(SDL_Renderer* renderer): _renderer{renderer} {}

void Printer_OneColor::receiveAllDrops(std::unordered_map<SpotType, std::unordered_set<Drop>> setOfDropsPerType, unordered_map<int, Box> boxesPerBoxId)
{
    print(setOfDropsPerType, boxesPerBoxId);
}

void Printer_OneColor::print(unordered_map<SpotType, unordered_set<Drop>> dropsPerType, unordered_map<int, Box> boxesPerBoxId)
{  
    (void)boxesPerBoxId; 
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);
    
    for (auto& setPerType : dropsPerType)
    {
        // TODO should this be a reference?
        unordered_set<Drop> setOfDrops = setPerType.second;
        
        for (auto& drop: setOfDrops)
        {
            // TODO Can I initialize a SDL_Rect in the constructor, instead of 4 lines?
            SDL_Rect squareRect;
            squareRect.w = 1;// TODO width and height is taken from box width and height not hardcoded
            squareRect.h = 1;
            squareRect.x = drop._position.getX();
            squareRect.y = drop._position.getY();

            SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0x00, 0xAA);
            SDL_RenderFillRect(_renderer, &squareRect);
        }
    }

    for(const pair<Position, Position>& endPoint : _endPoints)
    {
        Position topLeft = endPoint.first;
        Position bottomRight = endPoint.second;
        
        SDL_Rect endRect;
        endRect.x = topLeft.getX();
        endRect.y = topLeft.getY();
        endRect.w = bottomRight.getX() - topLeft.getX();
        endRect.h = bottomRight.getY() - topLeft.getY();
        SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(_renderer, &endRect);
    }

    SDL_RenderPresent(_renderer);
}

void Printer_OneColor::addEndPoint(Position topLeft, Position bottomRight)
{
    _endPoints.push_back({topLeft, bottomRight});
}
