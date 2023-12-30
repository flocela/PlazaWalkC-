#ifndef PRINTER__H
#define PRINTER__H

#include <memory>
#include <vector>
#include "Box.h"
#include "BoxNote.h"
#include "SDL.h"

class Printer
{

public:
    
    void print(SDL_Renderer* renderer, const std::vector<std::unique_ptr<Box>>& boxes);

private:
    
    bool isOpen(std::vector<BoxNote> boxNotes);

};

#endif
