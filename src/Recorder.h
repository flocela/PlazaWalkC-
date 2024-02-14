#ifndef RECORDER__H
#define RECORDER__H 

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "BoardAgentListener.h"
#include "RecorderListener.h"

class Recorder : public BoardAgentListener
{

public:
  
    Recorder();
    Recorder(const Recorder& o) = delete;
    Recorder(Recorder&& o) = delete;
    Recorder& operator=(const Recorder& o) = delete;
    Recorder& operator=(Recorder&& o) noexcept = delete;
    ~Recorder() noexcept = default; 

    // Need for typePerPosition memory to not be deleted until call is finished. 
    void receiveChanges(std::unordered_map<Position, int> typesPerPosition) override;

    std::unordered_map<int, std::unordered_set<Position>> getPositions();

    void registerListener(RecorderListener* listener);

private:
   
    std::unordered_map<int, std::unordered_set<Position>> _positionsetsPerType{}; 
    std::vector<RecorderListener*> _listeners;

};

#endif
