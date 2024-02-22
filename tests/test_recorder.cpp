#include "catch.hpp"
#include "../src/Recorder.h"

using namespace std;

class RecorderListenerTest : public RecorderListener
{
public:
    void receiveAllDrops(unordered_map<int, unordered_set<Drop>> setOfDropsPerType) override
    {
        _setOfDropsPerType = setOfDropsPerType;
    }
    unordered_map<int, unordered_set<Drop>> _setOfDropsPerType{};
};
     

TEST_CASE("incoming boxes are recorded")
{
    Recorder recorder{};
    RecorderListenerTest listener;
    recorder.registerListener(&listener);

    Drop dropA{0, 0}; // Drop at Position{0, 0}
    dropA._boxId = 0;
    dropA._type = 2;

    Drop dropB(2, 2); // Drop at Position{2, 2}
    dropB._boxId = 0;
    dropB._type = 2;

    // SCENARIO Receive two drops with different positions and the same type.
    unordered_map<int, unordered_set<Drop>> changedSetsOfDropsPerType{};
    unordered_set<Drop> dropsType2{};
    dropsType2.insert(dropA);
    dropsType2.insert(dropB);
    changedSetsOfDropsPerType.insert({2, dropsType2});

    recorder.receiveChanges(changedSetsOfDropsPerType);
    
    unordered_map<int, unordered_set<Drop>> actual = recorder.getDrops();
    REQUIRE(2 == actual.at(2).size());    
    REQUIRE(actual.find(-1) == actual.end());
    REQUIRE(actual.at(2).find(dropA) != actual.at(2).end());
    REQUIRE(actual.at(2).find(dropB) != actual.at(2).end());

    actual = listener._setOfDropsPerType;
    REQUIRE(2 == actual.at(2).size());    
    REQUIRE(actual.find(-1) == actual.end());
    REQUIRE(actual.at(2).find(dropA) != actual.at(2).end());
    REQUIRE(actual.at(2).find(dropB) != actual.at(2).end());
    
    // SCENARIO Receive one drop that replaces existing drop.
    dropB._type = 4;
    changedSetsOfDropsPerType = {};
    unordered_set<Drop> dropsType4{};
    dropsType4.insert(dropB);
    changedSetsOfDropsPerType.insert({4, dropsType4});

    recorder.receiveChanges(changedSetsOfDropsPerType);

    actual = recorder.getDrops();
    REQUIRE(1 == actual.at(2).size());    
    REQUIRE(1 == actual.at(4).size());
    REQUIRE(actual.at(2).find(dropA) != actual.at(2).end());
    REQUIRE(actual.at(4).find(dropB) != actual.at(4).end());

    actual = listener._setOfDropsPerType;
    REQUIRE(1 == actual.at(2).size());    
    REQUIRE(1 == actual.at(4).size());
    REQUIRE(actual.at(2).find(dropA) != actual.at(2).end());
    REQUIRE(actual.at(4).find(dropB) != actual.at(4).end());

    // SCENARIO Serially receive two drops with two different types.
    dropA._type = 4;
    changedSetsOfDropsPerType = {};
    dropsType4 = {};
    dropsType4.insert(dropA);
    changedSetsOfDropsPerType.insert({4, dropsType4});    
    recorder.receiveChanges(changedSetsOfDropsPerType);

    dropA._type = 1;
    changedSetsOfDropsPerType = {};
    unordered_set<Drop> dropsType1{};
    dropsType1.insert(dropA);
    changedSetsOfDropsPerType.insert({1, dropsType1});    
    recorder.receiveChanges(changedSetsOfDropsPerType);

    // add dropB._type = 4 to expected set
    dropsType4 = {};
    dropsType4.insert(dropB);
    changedSetsOfDropsPerType.insert({4, dropsType4});

    actual = recorder.getDrops();
    REQUIRE(1 == actual.at(1).size());    
    REQUIRE(1 == actual.at(4).size());
    REQUIRE(actual.at(1).find(dropA) != actual.at(2).end());
    REQUIRE(actual.at(4).find(dropB) != actual.at(4).end());

    actual = listener._setOfDropsPerType;
    REQUIRE(1 == actual.at(1).size());    
    REQUIRE(1 == actual.at(4).size());
    REQUIRE(actual.at(1).find(dropA) != actual.at(2).end());
    REQUIRE(actual.at(4).find(dropB) != actual.at(4).end());

    // SCENARIO Add drop with type 3

    dropA._type = -1;
    changedSetsOfDropsPerType = {};
    unordered_set<Drop> dropsTypeNeg1 = {};
    dropsTypeNeg1.insert(dropA);
    changedSetsOfDropsPerType.insert({-1, dropsTypeNeg1});    
    recorder.receiveChanges(changedSetsOfDropsPerType);

    changedSetsOfDropsPerType = {};
    
    // add dropB._type = 4 to expected set
    dropsType4 = {};
    dropsType4.insert(dropB);
    changedSetsOfDropsPerType.insert({4, dropsType4});

    actual = recorder.getDrops();
    REQUIRE(0 == actual.at(3).size());
    REQUIRE(1 == actual.at(4).size());
    REQUIRE(actual.at(4).find(dropB) != actual.at(4).end());

    actual = recorder.getDrops();
    REQUIRE(0 == actual.at(3).size());
    REQUIRE(1 == actual.at(4).size());
    REQUIRE(actual.at(4).find(dropB) != actual.at(4).end());
}



