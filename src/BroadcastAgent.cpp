#include "BroadcastAgent.h"

using namespace std;

// TODO this should be a const Board
BroadcastAgent::BroadcastAgent(Board* board)
:   _board{board}
{}

void BroadcastAgent::updateWithChanges()
{
    _board->sendChanges();
}

