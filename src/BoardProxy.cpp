#include "BoardProxy.h"

BoardProxy::BoardProxy(Board& o) :_board{o} 
{}

void BoardProxy::sendChanges()
{
    _board.sendChanges();
}
