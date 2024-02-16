#include "BoardAgent.h"
#include "Board.h"

using namespace std;

// TODO this should be a const Board
BoardAgent::BoardAgent(Board* board)
:   _board{board}
{}

void BoardAgent::updateWithChanges()
{
    _board->sendChanges();
}

