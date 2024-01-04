#ifndef BOXCHANGER__H
#define BOXCHANGER__H

#include "BoxNote.h"

class BoxChanger
{
public:

    virtual void addNote(BoxNote note) = 0;
};

#endif
