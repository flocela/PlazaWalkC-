#include "catch.hpp"
#include "../src/Recorder.h"
#include <iostream>

using namespace std;

/*
A RecorderListener that will listen for the Recorder's broadcasts and save the most recent data from the broadcast. The data is saved in public attributes _drops and _boxes. The tests access these attributes to verify what the Recorder broadcasted.
*/
class SubRecorderListener : public RecorderListener
{

    public:

    void receiveAllDropsAllBoxes(unordered_set<Drop> drops, unordered_map<int, BoxInfo> boxes) override
    {
        // Clear the saved attributes. _drops and _boxes should contain only the most recent broadcast data.
        _drops.clear();
        _boxes.clear();

        _drops = std::move(drops);
        for(const auto& p : boxes)
        {
            _boxes.insert({p.second.getId(), p.second});
        }        
    }

    unordered_set<Drop> _drops;
    unordered_map<int, BoxInfo> _boxes{};

};

/*
Returns the number of Drops per each SpotType.
*/
unordered_map<SpotType, int> getCountPerSpotType(unordered_set<Drop> drops)
{

    unordered_map<SpotType, int> countPerSpotType{};
    countPerSpotType.insert({SpotType::to_arrive, 0}); 
    countPerSpotType.insert({SpotType::arrive, 0}); 
    countPerSpotType.insert({SpotType::to_leave, 0}); 
    countPerSpotType.insert({SpotType::left, 0}); 

    for(const Drop& drop : drops)
    {
        if(drop.getSpotType() == SpotType::to_arrive)
        {
            ++countPerSpotType[SpotType::to_arrive];
        }
        else if (drop.getSpotType() == SpotType::arrive)
        {
            ++countPerSpotType[SpotType::arrive];
        }
        else if (drop.getSpotType() == SpotType::to_leave)
        {
            ++countPerSpotType[SpotType::to_leave];
        }
        else
        {
            ++countPerSpotType[SpotType::left];
        }
    }
    return countPerSpotType;
}


TEST_CASE("Recorder_core::")
{
    SECTION("Recorder receives the Drops that have changed. Verify that Recorder broadcasts current state of all the Drops to the listener.")
    {
        Recorder recorder{};
        SubRecorderListener subRecorderListener;
        recorder.registerListener(&subRecorderListener);

        // DropA at Position{0, 0}. SpotType::to_arrive.
        Drop dropA{0, 0};
        dropA.setBoxId(0);
        dropA.setSpotType(SpotType::to_arrive);

        // DropB at Position{2, 2}. SpotType::to_arrive.
        Drop dropB(2, 2);
        dropB.setBoxId(0);
        dropB.setSpotType(SpotType::to_arrive);

        // Recorder receives changedDrops containing two drops with different Positions and the same SpotType.
        unordered_set<Drop> changedDrops{};
        changedDrops.insert(dropA);
        changedDrops.insert(dropB);

        unordered_map<int, BoxInfo> boxesPerBoxIdDummy{};

        // recorder receives changedDrops.
        recorder.receiveChanges(changedDrops, boxesPerBoxIdDummy);

        // SubRecorderListener reflects that the Recorder sent the changed Drops.
        // dropA and dropB are both SpotType::to_arrive
        unordered_set<Drop> actual = subRecorderListener._drops;
        unordered_map<SpotType, int> actualCountPerSpotType = getCountPerSpotType(actual);
        REQUIRE(2 == actual.size());
        REQUIRE(2 == actualCountPerSpotType[SpotType::to_arrive]);
        REQUIRE(actual.find(dropA) != actual.end());
        REQUIRE(actual.find(dropB) != actual.end());

        
        // Recorder receives one drop that replaces the existing Drop, dropB.
        // dropA is SpotType::to_arrive, no change.
        // dropB is SpotType::arrive.
        actual.clear();
        changedDrops.clear();

        dropB.setSpotType(SpotType::arrive);
        changedDrops.insert(dropB);

        // recorder receives changedDrops.
        recorder.receiveChanges(changedDrops, boxesPerBoxIdDummy);

        actual.insert(subRecorderListener._drops.begin(), subRecorderListener._drops.end());
        actualCountPerSpotType = getCountPerSpotType(actual);
        REQUIRE(2 == actual.size());
        REQUIRE(1 == actualCountPerSpotType[SpotType::to_arrive]);
        REQUIRE(1 == actualCountPerSpotType[SpotType::arrive]);
        REQUIRE(actual.find(dropA) != actual.end());
        REQUIRE(actual.find(dropB) != actual.end());


        // dropA is set to SpotType::arrive.
        // dropB is set to SpotType::to_leave.
        actual.clear();
        changedDrops.clear();

        dropA.setSpotType(SpotType::arrive);
        dropB.setSpotType(SpotType::to_leave);
        changedDrops.insert(dropA);
        changedDrops.insert(dropB);

        // recorder receives changedDrops.
        recorder.receiveChanges(changedDrops, boxesPerBoxIdDummy);

        actual.insert(subRecorderListener._drops.begin(), subRecorderListener._drops.end());
        actualCountPerSpotType = getCountPerSpotType(actual);
        REQUIRE(2 == actual.size());
        REQUIRE(1 == actualCountPerSpotType[SpotType::arrive]);
        REQUIRE(1 == actualCountPerSpotType[SpotType::to_leave]);
        REQUIRE(actual.find(dropA) != actual.end());
        REQUIRE(actual.find(dropB) != actual.end());


        // dropA is set to SpotType::to_leave.
        // dropB is set to SpotType::left.
        actual.clear();
        changedDrops.clear();

        dropA.setSpotType(SpotType::to_leave);
        dropB.setSpotType(SpotType::left);
        changedDrops.insert(dropA);
        changedDrops.insert(dropB);

        // recorder receives changedDrops.
        recorder.receiveChanges(changedDrops, boxesPerBoxIdDummy);

        actual.insert(subRecorderListener._drops.begin(), subRecorderListener._drops.end());
        actualCountPerSpotType = getCountPerSpotType(actual);

        // Recorder only sends out Drops that contain a Box, so only sends out dropA.
        REQUIRE(1 == actual.size());
        REQUIRE(1 == actualCountPerSpotType[SpotType::to_leave]);
        REQUIRE(actual.find(dropA) != actual.end());
    }

    SECTION ("Recorder receives current state of Boxes. Verify that Recorder broadcasts that state.")
    {
        Recorder recorder{};
        SubRecorderListener subRecorderListener;
        recorder.registerListener(&subRecorderListener);

        unordered_set<Drop> dummyChangedDrops;

        unordered_map<int, BoxInfo> boxes = {
            {0, BoxInfo{0, 0, 3, 3, 0}},
            {1, BoxInfo{1, 0, 3, 3, 0}},
            {2,BoxInfo{2, 0, 3, 3, 0}}};

        recorder.receiveChanges(dummyChangedDrops, boxes);
        
        unordered_map<int, BoxInfo> actual = subRecorderListener._boxes;
       
        REQUIRE(3 == actual.size());
        REQUIRE(0 == actual.at(0).getId());
        REQUIRE(1 == actual.at(1).getId());
        REQUIRE(2 == actual.at(2).getId());
    }
}
