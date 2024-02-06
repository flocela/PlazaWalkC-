#ifndef PRINTER__H
#define PRINTER__H

#include "Board.h"
#include "BoardNote.h"
#include "Position.h"

class Printer
{

public:
    
    virtual void print(const Board& board, Position position) = 0;

};

#endif
