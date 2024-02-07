#include "BoardNote.h"
#include "Printer_OpaqueBox.h"

using namespace std;

Printer_OpaqueBox::Printer_OpaqueBox(SDL_Renderer* renderer): _renderer{renderer} {}

void Printer_OpaqueBox::print(const Board& board, Position position)
{  (void) board;
    (void) position; 
    (void) _renderer;
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

}
        
            
        

        
