#include "BoardCallback_Accountant.h"

using namespace std;

BoardCallback_Accountant::BoardCallback_Accountant(Board* board)
:   _board{board}
{}

void BoardCallback_Accountant::callback(Position position)
{
    BoardNote boardNote = _board->getNoteAt(position);
    _receivedBoardNotes.push_back({std::chrono::high_resolution_clock::now(), boardNote});
}

std::vector< std::pair< std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote > > BoardCallback_Accountant::getNotes() const
{
    return _receivedBoardNotes;
}

