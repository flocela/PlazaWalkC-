#ifndef BOARDPROXY__H
#define BOARDPROXY__H

class Board;
#include "Board.h"

class BoardProxy
{
    public:

    BoardProxy(Board& board);

    // Calls Board's sendChanges method.
    void sendChanges();


    private:

    Board& _board;
};

#endif
