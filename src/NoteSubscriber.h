#ifndef NOTESUBSCRIBER__H
#define NOTESUBSCRIBER__H

#include "BoardNote.h"
#include "Position.h"

class NoteSubscriber
{
public:
    virtual void callback(BoardNote boardnote, Position position) = 0;
};

#endif
