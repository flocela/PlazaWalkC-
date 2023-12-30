#include "Printer.h"

using namespace std;

void Printer::print(SDL_Renderer* renderer, const std::vector<unique_ptr<Box>>& boxes)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
// TODO take out auto and type in type
    for (const auto& box : boxes)
    {   (void) box;
        // create square with width 10.
        SDL_Rect squareRect;
        squareRect.w = 10;
        squareRect.h = 10;
/*
        const vector<BoxNote>& boxNotes = box.getNotes();
        const BoxNote& lastNote = *(--boxNotes.end());
        
        int lastNoteType = lastNote.getType();

        Position position = nullptr;
        
        // TODO need to check that time isn't past the printer's time.
        switch(lastNoteType)
        {
            case 1: // "arrive"
                position = new Position(lastNode.getCopyOfToPos());
                break;
            case 2: // "left"
                position = new Position(lastNode.getCopyOfFromPos());
                break;
            case 3: // "to arrive"
                position = new Position(lastNode.getCopyOfFromPos());
                break;
            case 4: // "to leave"
                position = new Position(lastNode.getCopyOfFromPos());
                break;
        }
        squareRect.x = position.getX();
        squareRect.y = position.getY();
*/
        
        
        //squareRect.x = box->getX();
        //squareRect.y = box->getY();
        //SDL_RenderFillRect(renderer, &squareRect);
    }

    SDL_RenderPresent(renderer);
    
}
        
            
        

        
