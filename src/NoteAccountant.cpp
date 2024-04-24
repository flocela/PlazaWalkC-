#include "NoteAccountant.h"

using namespace std;

NoteAccountant::NoteAccountant() {}

void NoteAccountant::callback(BoardNote boardNote)
{
    _receivedBoardNotes.push_back({std::chrono::high_resolution_clock::now(), boardNote});
}

std::vector< std::pair< std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote > > NoteAccountant::getNotes() const
{
    return _receivedBoardNotes;
}

