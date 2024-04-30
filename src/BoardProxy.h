#ifndef BOARDPROXY__H
#define BOARDPROXY__H

class Board;
#include "Board.h"

class BoardProxy
{
    public:

    // Calls Board's sendChanges method.
    void sendChanges();

    // Board is the only class that can construct a Board.    
    friend class Board;
    
    BoardProxy() = delete;
    BoardProxy(const BoardProxy& o) = default;
    BoardProxy(BoardProxy&& o) noexcept = default;
    BoardProxy& operator=(const BoardProxy& o) = delete;
    BoardProxy& operator=(BoardProxy&& o) noexcept = delete;
    ~BoardProxy() noexcept = default;

    private:

    BoardProxy(Board& board);

    Board& _board;
};

#endif
