#ifndef BOARDREADER__H
#define BOARDREADER__H

#include <unordered_map>
#include "BoardNote.h"

class BoardReader
{
public:
    
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    
    // returns unordered_map of BoardNotes per boxId.
    virtual std::unordered_map<int, BoardNote> getNotes(Position position) const = 0;
};

#endif
