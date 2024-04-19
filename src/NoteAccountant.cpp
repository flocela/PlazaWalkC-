#include "NoteAccountant.h"

using namespace std;

NoteAccountant::NoteAccountant() {}

// Adds the new BoardNote with a time stamp to a vector.
void NoteAccountant::callback(BoardNote boardNote, Position position)
{
    (void) position;
    _receivedBoardNotes.push_back({std::chrono::high_resolution_clock::now(), boardNote});
}

// Returns all the BoardNotes that have been seen. 
std::vector< std::pair< std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote > > NoteAccountant::getNotes() const
{
    return _receivedBoardNotes;
}

