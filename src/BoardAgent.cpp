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

void BoardAgent::receiveChanges(unordered_map<Position, int> typePerPosition)
{
    for (BoardAgentListener* listener : _listeners)
    {
        listener->receiveChanges(typePerPosition);
    }
}   

void BoardAgent::registerListener(BoardAgentListener* listener)
{
    _listeners.push_back(listener);
}
    
