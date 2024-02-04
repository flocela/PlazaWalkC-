#ifndef BOARDCALLBACK__H
#define BOARDCALLBACK__H

#include "BoardNote.h"
#include "Position.h"

class BoardCallback
{
public:
    virtual void callback(Position position) = 0;
};

#endif
