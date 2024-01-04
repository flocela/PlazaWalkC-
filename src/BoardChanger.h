#ifndef BOARDCHANGER__H
#define BOARDCHANGER__H

#include "Position.h"
#include "BoardNote.h"

class BoardChanger
{
public:
    
    virtual void addNote(Position position, BoardNote boardNote) = 0;

};

#endif
