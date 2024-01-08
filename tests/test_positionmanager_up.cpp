#include "catch.hpp"
#include "../src/PositionManager_Up.h"

using namespace std;

// box is moving up. If Current position is Position(a, b), then 
//      first position is Position(a, b-1). Corresponding to moving down.
//      second position is Position(a-1, b-1).
//      third position is Position(a+1, b-1).
TEST_CASE("Should return next positions, which are up, then the diagonal position up and right, then the diagonal position up and left.")
{
    // note0's type is 4, which means it arrives at Position(5, 5);
    BoxNote note0{4, Position{5, 5}, Position{5, 4}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
    box.addNote(note0);

    PositionManager_Up upPositionManager{Position{10, 10}};
    vector<Position> positions = upPositionManager.getFuturePositions(box);
    REQUIRE(positions[0] == Position{5, 4});
    REQUIRE(positions[1] == Position{6, 4});
    REQUIRE(positions[2] == Position{4, 4});

}

TEST_CASE("PositionManager_Up::atEnd() returns true if box has reached its final position.")
{
    // box has arrived at Position{1, 1}.    
    BoxNote note0{4, Position{1, 1}, Position{1, 1}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
    box.addNote(note0);
    PositionManager_Up upPositionManager(Position{1, 1});
    REQUIRE(true == upPositionManager.atEnd(box));
}

TEST_CASE("PositionManager_Up::atEnd() returns false if box is not at its final position.")
{
    // box has arrived at Position{0, 0}.    
    BoxNote note0{4, Position{0, 0}, Position{0, 0}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
    box.addNote(note0);
    PositionManager_Up upPositionManager(Position{1, 1});
    REQUIRE(false == upPositionManager.atEnd(box));
}


