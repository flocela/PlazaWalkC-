#ifndef RECORDER__H
#define RECORDER__H 

#include <vector>
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

    void receiveChanges(
        std::unordered_set<Drop> changedDrops,
        std::unordered_map<int, BoxInfo> boxes);

    void registerListener(RecorderListener* listener);

private:
   
    std::unordered_set<Drop> _drops{}; 
    std::vector<RecorderListener*> _listeners;

};

#endif
