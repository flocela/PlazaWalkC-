#include "Printer_OneColor.h"
#include <iostream>

using namespace std;

Printer_OneColor::Printer_OneColor(SDL_Renderer* renderer): _renderer{renderer} {}

void Printer_OneColor::receiveAllPositions(std::unordered_map<int, std::unordered_set<Position>> setOfPositionsPerType)
{
    print(setOfPositionsPerType);
}

void Printer_OneColor::print(unordered_map<int, unordered_set<Position>> positionsPerType)
{
    cout << "Printer_OneColor print" << endl;
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);
    cout << "positionPerType size: " << positionsPerType.size() <<endl;
    
    for (auto& setPerType : positionsPerType)
    {
        // TODO should this be a reference?
        unordered_set<Position> setOfPositions = setPerType.second;
        
        for (auto& position : setOfPositions)
        {
            // TODO Can I initialize a SDL_Rect in the constructor, instead of 4 lines?
            SDL_Rect squareRect;
            squareRect.w = 10;
            squareRect.h = 10;
            squareRect.x = position.getX();
            squareRect.y = position.getY();

            SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(_renderer, &squareRect);
            cout << "printing square" << endl;
        }
    }
    cout << "PRinter_OnceColor.cpp SDL_RendererPresent" << endl;
    SDL_RenderPresent(_renderer);
}
