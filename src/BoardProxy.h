#ifndef BOARDPROXY__H
#define BOARDPROXY__H

class Board;
#include "Board.h"

class BoardProxy
{
    public:

    // Calls Board's sendChanges method.
    void sendChanges();
    
    friend class Board;


    private:

    BoardProxy(Board& board);
    Board& _board;
};

#endif
