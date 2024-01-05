#ifndef BOARDCALLBACK__H
#define BOARDCALLBACK__H

#include <unordered_map>
#include <utility>
#include <vector>

#include "BoardNote.h"

class BoardCallback
{
public:
    void callBack(std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, std::unordered_map<int, BoardNote>> timeStampAndUnorderedMapOfBoardnotePerBoxId);

    
private:
   std::vector< std::pair< std::chrono::time_point<std::chrono::high_resolution_clock>, std::unordered_map<int, BoardNote> > > _timeStampedBoardNotes; 

};

#endif
   
