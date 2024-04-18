#ifndef BOARDPROXY__H
#define BOARDPROXY__H

#include "Board.h"

class BoardProxy
{
public:
    BoardProxy(Board& board);
    BoardProxy() = delete;
    BoardProxy(const BoardProxy& o) = delete;
    BoardProxy(BoardProxy&& o) noexcept;
    BoardProxy& operator=(const BoardProxy& o) = delete;
    BoardProxy& operator=(BoardProxy& o) noexcept = delete;
    ~BoardProxy() = default;

    // Calls Board's sendChanges method.
    void sendChanges();

private:
    Board& _board;
};

#endif
