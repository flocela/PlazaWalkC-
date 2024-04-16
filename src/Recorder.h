#ifndef RECORDER__H
#define RECORDER__H 

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "BoardListener.h"
#include "RecorderListener.h"

class Recorder : public BoardListener
{

public:
  
    Recorder();
    Recorder(const Recorder& o) = delete;
    Recorder(Recorder&& o) = delete;
    Recorder& operator=(const Recorder& o) = delete;
    Recorder& operator=(Recorder&& o) noexcept = delete;
    ~Recorder() noexcept = default; 

    // Need for typePerPosition memory to not be deleted until call is finished. 
    // Has a cumulative set of drops per type. But only keeps types 1, 2, and 4.
    void receiveChanges(std::unordered_map<SpotType, std::unordered_set<Drop>> setsOfDropsPerType, std::unordered_map<int, BoxInfo> boxes);

    std::unordered_map<SpotType, std::unordered_set<Drop>> getDrops();

    void registerListener(RecorderListener* listener);

private:
   
    std::unordered_map<SpotType, std::unordered_set<Drop>> _dropSetsPerType{}; 
    std::vector<RecorderListener*> _listeners;

};

#endif
