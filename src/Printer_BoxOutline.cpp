#include "Printer_BoxOutline.h"

using namespace std;

void Printer_BoxOutline::print(SDL_Renderer* renderer, const std::vector<unique_ptr<Box>>& boxes)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
// TODO take out auto and type in type

    for (const auto& box : boxes)
    {   
        // Square's information.
        Position pos = box->getPosition(); 
        
        // Creating square with width 9, requires 4 lines to outlining the square.

        // Top horizontal line.
        SDL_Rect topLine;
        topLine.w = 9;
        topLine.h = 1;
        topLine.x = pos.getX() - 4;
        topLine.y = pos.getY() - 4;
        SDL_RenderFillRect(renderer, &topLine);
        
        // Bottom horizontal line.
        SDL_Rect bottomLine;
        bottomLine.w = 9;
        bottomLine.h = 1;
        bottomLine.x = pos.getX() - 4;
        bottomLine.y = pos.getY() + 4;
        SDL_RenderFillRect(renderer, &bottomLine);
        
        // Left vertical line.
        SDL_Rect leftLine;
        leftLine.w = 1;
        leftLine.h = 9;
        leftLine.x = pos.getX() - 4;
        leftLine.y = pos.getY() - 4;
        SDL_RenderFillRect(renderer, &leftLine);
        
        // Right vertical line.
        SDL_Rect rightLine;
        rightLine.w = 1;
        rightLine.h = 9;
        rightLine.x = pos.getX() + 4;
        rightLine.y = pos.getY() - 4;
        SDL_RenderFillRect(renderer, &rightLine);
    }

    SDL_RenderPresent(renderer);
    
}
        
            
        

        
