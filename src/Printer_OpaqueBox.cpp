#include "Printer_OpaqueBox.h"

using namespace std;

void Printer_OpaqueBox::print(SDL_Renderer* renderer, const std::vector<unique_ptr<Box>>& boxes)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
// TODO take out auto and type in type

    for (const auto& box : boxes)
    {   
        Position pos = box->getPosition(); 
    
        // create square with width 10.
        SDL_Rect squareRect;
        squareRect.w = 10;
        squareRect.h = 10;
        squareRect.x = pos.getX();
        squareRect.y = pos.getY();
        SDL_RenderFillRect(renderer, &squareRect);
    }

    SDL_RenderPresent(renderer);
    
}
        
            
        

        
