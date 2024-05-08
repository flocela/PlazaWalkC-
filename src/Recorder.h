#ifndef RECORDER__H
#define RECORDER__H 

#include <vector>
#include <unordered_set>
#include "BoardListener.h"
#include "RecorderListener.h"

/*
Receives changes to Drops and state of all Boxes from the Board. It then processes this data and sends out the data to its RecorderListeners.*/
class Recorder : public BoardListener
{

    public:
  
    Recorder();
    Recorder(const Recorder& o) = delete;
    Recorder(Recorder&& o) = delete;
    Recorder& operator=(const Recorder& o) = delete;
    Recorder& operator=(Recorder&& o) noexcept = delete;
    ~Recorder() noexcept = default; 

    /*
    Keeps a running unordered_set of the Drops that currently contain Boxes. (In this sense it contains a tally of the Boxes that are on the Board.) When it receives the changedDrops it updates this set by removing Drops that no long contain a Box and updates the Drops that have changed. (Maybe their SpotType or level has changed.) There is no processing of the Boxes received. The running set of the Drops and the received Boxes are then broadcasted out to its RecorderListeners.
    */
    void receiveChanges(
        std::unordered_set<Drop> changedDrops,
        std::unordered_map<int, BoxInfo> boxes);

    void registerListener(RecorderListener* listener);


    private:

    // _drops only saves Drops that do not have SpotType::left. _drops represents all the Drops on the Board that have a Box. When a Box leaves a Drop, Recorder receives a Drop with a SpotType::left and the Drop is removed from _drops.
    std::unordered_set<Drop> _drops{}; 
    std::vector<RecorderListener*> _listeners;

};

#endif
