#include "catch.hpp"
#include "../src/Recorder.h"
#include <iostream>

using namespace std;

class SubRecorderListener : public RecorderListener
{
public:
    void receiveAllDropsAllBoxes(unordered_set<Drop> drops, unordered_map<int, BoxInfo> boxes) override
    {
        _drops.clear();
        _drops = std::move(drops);
        for(const auto& p : boxes)
        {
            _boxes.insert({p.second.getId(), p.second});
        }        
    }

    unordered_set<Drop> _drops;
    unordered_map<int, BoxInfo> _boxes{};
};

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

TEST_CASE("Recorder receives individual changes to Drops. Broadcast current state of Drops to listeners.")
{
    Recorder recorder{};
    SubRecorderListener subRecorderListener;
    recorder.registerListener(&subRecorderListener);

    Drop dropA{0, 0}; // Drop at Position{0, 0}
    dropA.setBoxId(0);
    dropA.setSpotType(SpotType::to_arrive);

    Drop dropB(2, 2); // Drop at Position{2, 2}
    dropB.setBoxId(0);
    dropB.setSpotType(SpotType::to_arrive);

    // Receive two drops with different positions and the same type.
    unordered_set<Drop> changedDrops{};
    changedDrops.insert(dropA);
    changedDrops.insert(dropB);

    unordered_map<int, BoxInfo> boxesPerBoxIdDummy{};

    recorder.receiveChanges(changedDrops, boxesPerBoxIdDummy);

    // The Recorder sent the new state of the drops and boxes, because the SubRecorderListener got them. 
    // dropA and dropB are both SpotType::to_arrive
    unordered_set<Drop> actual_0 = subRecorderListener._drops;
    unordered_map<SpotType, int> actualCountPerSpotType = getCountPerSpotType(actual_0);
    REQUIRE(2 == actual_0.size());
    REQUIRE(2 == actualCountPerSpotType[SpotType::to_arrive]);
    REQUIRE(actual_0.find(dropA) != actual_0.end());
    REQUIRE(actual_0.find(dropB) != actual_0.end());
    
    // recorder receives one drop that replaces existing drop.
    // No change to dropA (SpotType::to_arrive), dropB set to SpotType::arrive.
    dropB.setSpotType(SpotType::arrive);
    changedDrops.clear();
    changedDrops.insert(dropB);

    recorder.receiveChanges(changedDrops, boxesPerBoxIdDummy);

    unordered_set<Drop> actual_1 = subRecorderListener._drops;
    actualCountPerSpotType = getCountPerSpotType(actual_1);
    REQUIRE(2 == actual_1.size());
    REQUIRE(1 == actualCountPerSpotType[SpotType::to_arrive]);
    REQUIRE(1 == actualCountPerSpotType[SpotType::arrive]);
    REQUIRE(actual_1.find(dropA) != actual_1.end());
    REQUIRE(actual_1.find(dropB) != actual_1.end());

    // Serially receive two drops with two different types.
    // dropA changes to SpotType::arrive. dropB changes to SpotType::to_leave.
    dropA.setSpotType(SpotType::arrive);
    changedDrops.clear();
    changedDrops.insert(dropA);

    recorder.receiveChanges(changedDrops, boxesPerBoxIdDummy);

    unordered_set<Drop> actual_2 = subRecorderListener._drops;
    actualCountPerSpotType = getCountPerSpotType(actual_2);
    REQUIRE(2 == actual_2.size());
    REQUIRE(2 == actualCountPerSpotType[SpotType::arrive]);
    REQUIRE(actual_2.find(dropA) != actual_2.end());
    REQUIRE(actual_2.find(dropB) != actual_2.end());
   
    dropB.setSpotType(SpotType::to_leave);
    changedDrops.clear();
    changedDrops.insert(dropB);

    recorder.receiveChanges(changedDrops, boxesPerBoxIdDummy);

    unordered_set<Drop> actual_3 = subRecorderListener._drops;
    actualCountPerSpotType = getCountPerSpotType(actual_3);
    REQUIRE(2 == actual_3.size());
    REQUIRE(1 == actualCountPerSpotType[SpotType::arrive]);
    REQUIRE(1 == actualCountPerSpotType[SpotType::to_leave]);
    REQUIRE(actual_3.find(dropA) != actual_3.end());
    REQUIRE(actual_3.find(dropB) != actual_3.end());
}

TEST_CASE ("Recorder receives current state of Boxes and broadcasts that state.")
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
