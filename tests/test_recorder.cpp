#include "catch.hpp"
#include "../src/Recorder.h"
#include <iostream>

using namespace std;

class RecorderListenerTest : public RecorderListener
{
public:
    void receiveAllDrops(unordered_map<SpotType, unordered_set<Drop>> setOfDropsPerType, unordered_map<int, BoxInfo> boxes) override
    {
        _setOfDropsPerType = setOfDropsPerType;
        for(const auto& p : boxes)
        {
            _boxes.insert({p.second.getId(), p.second});
        }        
    }

    unordered_map<SpotType, unordered_set<Drop>> _setOfDropsPerType{};
    unordered_map<int, BoxInfo> _boxes{};
};
     

TEST_CASE("incoming boxes are recorded")
{
    Recorder recorder{};
    RecorderListenerTest listener;
    recorder.registerListener(&listener);

    Drop dropA{0, 0}; // Drop at Position{0, 0}
    dropA._boxId = 0;
    dropA._type = SpotType::to_arrive;

    Drop dropB(2, 2); // Drop at Position{2, 2}
    dropB._boxId = 0;
    dropB._type = SpotType::to_arrive;

    // SCENARIO Receive two drops with different positions and the same type.
    unordered_map<SpotType, unordered_set<Drop>> changedSetsOfDropsPerType{};
    unordered_set<Drop> dropsType2{};
    dropsType2.insert(dropA);
    dropsType2.insert(dropB);
    changedSetsOfDropsPerType.insert({SpotType::to_arrive, dropsType2});

    unordered_map<int, BoxInfo> boxesPerBoxIdDummy{};

    recorder.receiveChanges(changedSetsOfDropsPerType, boxesPerBoxIdDummy);
    
    unordered_map<SpotType, unordered_set<Drop>> actual = recorder.getDrops();
    REQUIRE(2 == actual.at(SpotType::to_arrive).size());    
    REQUIRE(0 == actual[SpotType::left].size());
    REQUIRE(actual.at(SpotType::to_arrive).find(dropA) != actual.at(SpotType::to_arrive).end());
    REQUIRE(actual.at(SpotType::to_arrive).find(dropB) != actual.at(SpotType::to_arrive).end());

    actual = listener._setOfDropsPerType;
    REQUIRE(2 == actual.at(SpotType::to_arrive).size());    
    REQUIRE(0 == actual[SpotType::left].size());
    REQUIRE(actual.at(SpotType::to_arrive).find(dropA) != actual.at(SpotType::to_arrive).end());
    REQUIRE(actual.at(SpotType::to_arrive).find(dropB) != actual.at(SpotType::to_arrive).end());
    
    // SCENARIO Receive one drop that replaces existing drop.
    dropB._type = SpotType::arrive;
    changedSetsOfDropsPerType = {};
    unordered_set<Drop> dropsType4{};
    dropsType4.insert(dropB);
    changedSetsOfDropsPerType.insert({SpotType::arrive, dropsType4});

    recorder.receiveChanges(changedSetsOfDropsPerType, boxesPerBoxIdDummy);

    actual = recorder.getDrops();
    REQUIRE(1 == actual.at(SpotType::to_arrive).size());    
    REQUIRE(1 == actual.at(SpotType::arrive).size());
    REQUIRE(actual.at(SpotType::to_arrive).find(dropA) != actual.at(SpotType::to_arrive).end());
    REQUIRE(actual.at(SpotType::arrive).find(dropB) != actual.at(SpotType::arrive).end());

    actual = listener._setOfDropsPerType;
    REQUIRE(1 == actual.at(SpotType::to_arrive).size());    
    REQUIRE(1 == actual.at(SpotType::arrive).size());
    REQUIRE(actual.at(SpotType::to_arrive).find(dropA) != actual.at(SpotType::to_arrive).end());
    REQUIRE(actual.at(SpotType::arrive).find(dropB) != actual.at(SpotType::arrive).end());

    // SCENARIO Serially receive two drops with two different types.
    dropA._type = SpotType::arrive;
    changedSetsOfDropsPerType = {};
    dropsType4 = {};
    dropsType4.insert(dropA);
    changedSetsOfDropsPerType.insert({SpotType::arrive, dropsType4});    
    recorder.receiveChanges(changedSetsOfDropsPerType, boxesPerBoxIdDummy);

    dropA._type = SpotType::to_leave;
    changedSetsOfDropsPerType = {};
    unordered_set<Drop> dropsType1{};
    dropsType1.insert(dropA);
    changedSetsOfDropsPerType.insert({SpotType::to_leave, dropsType1});    
    recorder.receiveChanges(changedSetsOfDropsPerType, boxesPerBoxIdDummy);

    // add dropB._type = 4 to expected set
    dropsType4 = {};
    dropsType4.insert(dropB);
    changedSetsOfDropsPerType.insert({SpotType::arrive, dropsType4});

    actual = recorder.getDrops();
    REQUIRE(1 == actual.at(SpotType::to_leave).size());    
    REQUIRE(1 == actual.at(SpotType::arrive).size());
    REQUIRE(actual.at(SpotType::to_leave).find(dropA) != actual.at(SpotType::to_arrive).end());
    REQUIRE(actual.at(SpotType::arrive).find(dropB) != actual.at(SpotType::arrive).end());

    actual = listener._setOfDropsPerType;
    REQUIRE(1 == actual.at(SpotType::to_leave).size());    
    REQUIRE(1 == actual.at(SpotType::arrive).size());
    REQUIRE(actual.at(SpotType::to_leave).find(dropA) != actual.at(SpotType::to_arrive).end());
    REQUIRE(actual.at(SpotType::arrive).find(dropB) != actual.at(SpotType::arrive).end());

    // SCENARIO Add drop with type 3

    dropA._type = SpotType::left;
    changedSetsOfDropsPerType = {};
    unordered_set<Drop> dropsTypeNeg1 = {};
    dropsTypeNeg1.insert(dropA);
    changedSetsOfDropsPerType.insert({SpotType::left, dropsTypeNeg1});    
    recorder.receiveChanges(changedSetsOfDropsPerType, boxesPerBoxIdDummy);

    changedSetsOfDropsPerType = {};
    
    // add dropB._type = 4 to expected set
    dropsType4 = {};
    dropsType4.insert(dropB);
    changedSetsOfDropsPerType.insert({SpotType::arrive, dropsType4});

    actual = recorder.getDrops();
    REQUIRE(0 == actual.at(SpotType::left).size());
    REQUIRE(1 == actual.at(SpotType::arrive).size());
    REQUIRE(actual.at(SpotType::arrive).find(dropB) != actual.at(SpotType::arrive).end());

    actual = recorder.getDrops();
    REQUIRE(0 == actual.at(SpotType::left).size());
    REQUIRE(1 == actual.at(SpotType::arrive).size());
    REQUIRE(actual.at(SpotType::arrive).find(dropB) != actual.at(SpotType::arrive).end());
}

TEST_CASE ("boxes are received")
{
    Recorder recorder{};
    RecorderListenerTest listener;
    recorder.registerListener(&listener);

    unordered_map<SpotType, unordered_set<Drop>> changedSetsOfDropsPerTypeDummy{};
    unordered_map<int, BoxInfo> boxesPerBoxIdDummy{};

    // Box(int id, int width, int height);
    unordered_map<int, BoxInfo> boxes = {
        {0, BoxInfo{0, 0, 3, 3, 0}}, {1, BoxInfo{1, 0, 3, 3, 0}}, {2,BoxInfo{2, 0, 3, 3, 0}}};

    recorder.receiveChanges(changedSetsOfDropsPerTypeDummy, boxes);
    
    unordered_map<int, BoxInfo> actual = listener._boxes;
   
    REQUIRE(3 == actual.size());
    REQUIRE(0 == actual.at(0).getId());
    REQUIRE(1 == actual.at(1).getId());
    REQUIRE(2 == actual.at(2).getId());

}
