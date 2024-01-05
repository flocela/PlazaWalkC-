#include "BoardCallback.h"

void BoardCallback::callBack(std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, std::unordered_map<int, BoardNote>> timeStampAndUnorderedMapOfBoardnotePerBoxId)
{
    _timeStampedBoardNotes.push_back(timeStampAndUnorderedMapOfBoardnotePerBoxId);
}
