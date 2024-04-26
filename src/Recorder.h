#ifndef RECORDER__H
#define RECORDER__H 

#include <vector>
#include <unordered_set>
#include "BoardListener.h"
#include "RecorderListener.h"

// Receives changes to Drops and current state of the Boxes, processes the data, then broadcasts the current state of all the Drops and Boxes.
// Since it only receives changes to Drops, it must keeping a running state of all the Drops and add the changes as they are received.
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

    // _drops keeps received Drops that do not have SpotType::left. It represents all the Drops on the Board that have a Box on them. When a Box leaves a Drop, Recorder receives a Drop with a SpotType::left and the Drop is removed from _drops.
    std::unordered_set<Drop> _drops{}; 
    std::vector<RecorderListener*> _listeners;

};

#endif
