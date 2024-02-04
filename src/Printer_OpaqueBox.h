#ifndef PRINTER_OPAQUEBOX__H
#define PRINTER_OPAQUEBOX__H

#include "Printer.h"
#include "SDL.h"

class Printer_OpaqueBox : public Printer
{

public:
    Printer_OpaqueBox() = delete;
    Printer_OpaqueBox(SDL_Renderer* renderer);
    Printer_OpaqueBox(const Printer_OpaqueBox& o) = delete;
    Printer_OpaqueBox(Printer_OpaqueBox&& o) noexcept = delete;
    Printer_OpaqueBox& operator=(const Printer_OpaqueBox& o) = delete;
    Printer_OpaqueBox& operator=(Printer_OpaqueBox&& o) noexcept = delete;
    ~Printer_OpaqueBox() = default;
    
    void print(const Board& board, Position position) override;

private:
    SDL_Renderer* _renderer;

};

#endif
