#ifndef RECORDER__H
#define RECORDER__H 

#include <unordered_map>
#include <unordered_set>
#include "BoardNote.h"
#include "Position.h"

class Recorder 
{

public:
   
    // Need for typePerPosition memory to not be deleted until call is finished. 
    void receiveChanges(std::unordered_map<Position, int>& typePerPosition);

    std::unordered_map<int, std::unordered_set<Position>> getPositions();

private:
   
    std::unordered_map<int, std::unordered_set<Position>> _positionSetsPerType{}; 

};

#endif
