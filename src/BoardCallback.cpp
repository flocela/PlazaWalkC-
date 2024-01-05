#include "BoardCallback.h"

using namespace std;

void BoardCallback::callBack(std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, std::unordered_map<int, BoardNote>> timeStampAndUnorderedMapOfBoardnotePerBoxId)
{
    _timeStampedBoardNotes.push_back(timeStampAndUnorderedMapOfBoardnotePerBoxId);
}

vector< std::pair< std::chrono::time_point<std::chrono::high_resolution_clock>, std::unordered_map<int, BoardNote> > > BoardCallback::getNotes()
{
    return _timeStampedBoardNotes;
}
