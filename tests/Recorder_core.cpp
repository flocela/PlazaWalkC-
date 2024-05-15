#include "catch.hpp"
#include "../src/Recorder.h"

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
Returns the number of Drops per each MoveType.
*/
unordered_map<MoveType, int> getCountPerMoveType(unordered_set<Drop> drops)
{

    unordered_map<MoveType, int> countPerMoveType{};
    countPerMoveType.insert({MoveType::to_arrive, 0}); 
    countPerMoveType.insert({MoveType::arrive, 0}); 
    countPerMoveType.insert({MoveType::to_leave, 0}); 
    countPerMoveType.insert({MoveType::left, 0}); 

    for(const Drop& drop : drops)
    {
        if(drop.getMoveType() == MoveType::to_arrive)
        {
            ++countPerMoveType[MoveType::to_arrive];
        }
        else if (drop.getMoveType() == MoveType::arrive)
        {
            ++countPerMoveType[MoveType::arrive];
        }
        else if (drop.getMoveType() == MoveType::to_leave)
        {
            ++countPerMoveType[MoveType::to_leave];
        }
        else
        {
            ++countPerMoveType[MoveType::left];
        }
    }
    return countPerMoveType;
}


TEST_CASE("Recorder_core::")
{
    SECTION("Recorder receives the Drops that have changed. Verify that Recorder broadcasts current state of all the Drops to the listener.")
    {
        Recorder recorder{};
        SubRecorderListener subRecorderListener;
        recorder.registerListener(&subRecorderListener);

        // DropA at Position{0, 0}. MoveType::to_arrive.
        Drop dropA{0, 0};
        dropA.setBoxId(0);
        dropA.setMoveType(MoveType::to_arrive);

        // DropB at Position{2, 2}. MoveType::to_arrive.
        Drop dropB(2, 2);
        dropB.setBoxId(0);
        dropB.setMoveType(MoveType::to_arrive);

        // Recorder receives changedDrops containing two drops with different Positions and the same MoveType.
        unordered_set<Drop> changedDrops{};
        changedDrops.insert(dropA);
        changedDrops.insert(dropB);

        unordered_map<int, BoxInfo> boxesPerBoxIdDummy{};

        // recorder receives changedDrops.
        recorder.receiveChanges(changedDrops, boxesPerBoxIdDummy);

        // SubRecorderListener reflects that the Recorder sent the changed Drops.
        // dropA and dropB are both MoveType::to_arrive
        unordered_set<Drop> actual = subRecorderListener._drops;
        unordered_map<MoveType, int> actualCountPerMoveType = getCountPerMoveType(actual);
        REQUIRE(2 == actual.size());
        REQUIRE(2 == actualCountPerMoveType[MoveType::to_arrive]);
        REQUIRE(actual.find(dropA) != actual.end());
        REQUIRE(actual.find(dropB) != actual.end());

        
        // Recorder receives one drop that replaces the existing Drop, dropB.
        // dropA is MoveType::to_arrive, no change.
        // dropB is MoveType::arrive.
        actual.clear();
        changedDrops.clear();

        dropB.setMoveType(MoveType::arrive);
        changedDrops.insert(dropB);

        // recorder receives changedDrops.
        recorder.receiveChanges(changedDrops, boxesPerBoxIdDummy);

        actual.insert(subRecorderListener._drops.begin(), subRecorderListener._drops.end());
        actualCountPerMoveType = getCountPerMoveType(actual);
        REQUIRE(2 == actual.size());
        REQUIRE(1 == actualCountPerMoveType[MoveType::to_arrive]);
        REQUIRE(1 == actualCountPerMoveType[MoveType::arrive]);
        REQUIRE(actual.find(dropA) != actual.end());
        REQUIRE(actual.find(dropB) != actual.end());


        // dropA is set to MoveType::arrive.
        // dropB is set to MoveType::to_leave.
        actual.clear();
        changedDrops.clear();

        dropA.setMoveType(MoveType::arrive);
        dropB.setMoveType(MoveType::to_leave);
        changedDrops.insert(dropA);
        changedDrops.insert(dropB);

        // recorder receives changedDrops.
        recorder.receiveChanges(changedDrops, boxesPerBoxIdDummy);

        actual.insert(subRecorderListener._drops.begin(), subRecorderListener._drops.end());
        actualCountPerMoveType = getCountPerMoveType(actual);
        REQUIRE(2 == actual.size());
        REQUIRE(1 == actualCountPerMoveType[MoveType::arrive]);
        REQUIRE(1 == actualCountPerMoveType[MoveType::to_leave]);
        REQUIRE(actual.find(dropA) != actual.end());
        REQUIRE(actual.find(dropB) != actual.end());


        // dropA is set to MoveType::to_leave.
        // dropB is set to MoveType::left.
        actual.clear();
        changedDrops.clear();

        dropA.setMoveType(MoveType::to_leave);
        dropB.setMoveType(MoveType::left);
        changedDrops.insert(dropA);
        changedDrops.insert(dropB);

        // recorder receives changedDrops.
        recorder.receiveChanges(changedDrops, boxesPerBoxIdDummy);

        actual.insert(subRecorderListener._drops.begin(), subRecorderListener._drops.end());
        actualCountPerMoveType = getCountPerMoveType(actual);

        // Recorder only sends out Drops that contain a Box, so only sends out dropA.
        REQUIRE(1 == actual.size());
        REQUIRE(1 == actualCountPerMoveType[MoveType::to_leave]);
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
