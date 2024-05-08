#ifndef NOTESUBSCRIBER__H
#define NOTESUBSCRIBER__H

#include "BoardNote.h"
#include "Position.h"

/*
Receives BoardNotes through the callback() method. Each received BoardNote is stamped with the current time.
Returns received BoardNotes with their time stamps through the getNotes() method.
*/
class NoteSubscriber
{
public:
    
    virtual void callback(BoardNote boardnote) = 0;

    virtual std::vector<std::pair< std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote >> getNotes() const = 0;
};

#endif
