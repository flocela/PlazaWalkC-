#include "BoardRecorderAgent.h"
#include "Board.h"

using namespace std;

// TODO this should be a const Board
BoardRecorderAgent::BoardRecorderAgent(Board* board, Recorder* recorder)
:   _board{board},
    _recorder{recorder}
{}

void BoardRecorderAgent::updateWithChanges()
{
    _board->sendChanges();
}

void BoardRecorderAgent::receiveChanges(unordered_map<Position, int> typePerPosition)
{
    _recorder->receiveChanges(typePerPosition);
}   
