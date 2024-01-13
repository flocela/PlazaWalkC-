#ifndef PRINTER_OPAQUEBOX__H
#define PRINTER_OPAQUEBOX__H

#include <memory>
#include <vector>
#include "Box.h"
#include "BoxNote.h"
#include "Printer.h"
#include "SDL.h"

class Printer_OpaqueBox : public Printer
{

public:
    
    void print(SDL_Renderer* renderer, const std::vector<std::unique_ptr<Box>>& boxes) override;

};

#endif
