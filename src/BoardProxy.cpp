#include "BoardProxy.h"

BoardProxy::BoardProxy(BoardProxy&& o)noexcept :_board{o._board} 
{}

void BoardProxy::sendChanges()
{
    _board.sendChanges();
}
