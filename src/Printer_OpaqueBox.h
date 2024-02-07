#ifndef PRINTER_OPAQUEBOX__H
#define PRINTER_OPAQUEBOX__H

#include <shared_mutex>
#include "Printer.h"
#include "SDL.h"

class Printer_OpaqueBox : public Printer
{

public:
    Printer_OpaqueBox();
    Printer_OpaqueBox(const Printer_OpaqueBox& o) = delete;
    Printer_OpaqueBox(Printer_OpaqueBox&& o) noexcept = delete;
    Printer_OpaqueBox& operator=(const Printer_OpaqueBox& o) = delete;
    Printer_OpaqueBox& operator=(Printer_OpaqueBox&& o) noexcept = delete;
    ~Printer_OpaqueBox() = default;
    
    void print(const Board& board, Position position) override;

private:

};

#endif
