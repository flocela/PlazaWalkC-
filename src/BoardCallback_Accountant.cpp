#include "BoardCallback_Accountant.h"

using namespace std;

BoardCallback_Accountant::BoardCallback_Accountant() {}

// Adds the new BoardNote with a time stamp to a vector.
void BoardCallback_Accountant::callback(BoardNote boardNote, Position position)
{
    (void) position;
    _receivedBoardNotes.push_back({std::chrono::high_resolution_clock::now(), boardNote});
}

// Returns all the BoardNotes that have been seen. 
std::vector< std::pair< std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote > > BoardCallback_Accountant::getNotes() const
{
    return _receivedBoardNotes;
}

