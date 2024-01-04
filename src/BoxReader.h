#ifndef BOXREADER__H
#define BOXREADER__H

#include "BoxNote.h"
#include "Position.h"

class BoxReader
{
public:
    
    virtual int getId() const = 0;    
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    virtual Position getPos(std::chrono::time_point<std::chrono::high_resolution_clock> cutOffTime) const = 0;

    virtual std::vector<BoxNote> getAllNotes() const = 0;
    virtual std::vector<BoxNote> getLastNotes(int count) const = 0;
};

#endif
