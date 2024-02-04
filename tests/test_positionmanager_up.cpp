#include "catch.hpp"
#include "../src/PositionManager_Up.h"

using namespace std;

// box is moving up. If Current position is Position(a, b), then first position is Position(a, b-1). Corresponding to moving up. Second position is Position(a-1, b-1). Third position is Position(a+1, b-1).
TEST_CASE("Should return next positions, which are up, then the diagonal up and right position, then the diagonal up and left position.")
{
    // note0's type is 4, which means it arrives at Position(5, 5);
    BoxNote note0{4, Position{5, 5}, Position{5, 5}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};

    PositionManager_Up upPositionManager{0, 0, 10, 0, 10};
    vector<Position> positions = upPositionManager.getFuturePositions(box);
    REQUIRE(positions.size() == 3);
    REQUIRE(positions[0] == Position{5, 4});
    REQUIRE(positions[1] == Position{6, 4});
    REQUIRE(positions[2] == Position{4, 4});
}

TEST_CASE("PositionManager_Up::atEnd() returns true if box has reached its final position.")
{
    // box has arrived at Position{1, 1}.    
    BoxNote note0{4, Position{1, 1}, Position{1, 1}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
    PositionManager_Up upPositionManager(1, 0, 10, 0, 10);
    REQUIRE(true == upPositionManager.atEnd(box));
}

TEST_CASE("PositionManager_Up::atEnd() returns false if box is not at its final position.")
{
    // box has arrived at Position{2, 2}.    
    BoxNote note0{4, Position{2, 2}, Position{2, 2}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
    PositionManager_Up upPositionManager(1, 0, 10, 0, 10);
    REQUIRE(false == upPositionManager.atEnd(box));
}

TEST_CASE("PositionManager_Up:: box's current position is already at end, then getFuturePositions returns an empty vector.")
{
    // box is at Position{0, 0}.
    BoxNote note0{4, Position{0, 0}, Position{0, 0}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
   
    // final y is at y = 0. Board is a 20x20 board.
    PositionManager_Up upPositionManager{0, 0, 19, 0, 19};
    REQUIRE(vector<Position>{} == upPositionManager.getFuturePositions(box));
}

TEST_CASE("PositionManager_Up:: getFuturePositions doesn't return any positions that are off the board. Testing where box would have a next position with an x larger than board.size()-1")
{
    // box is at Position{19, 1}.
    BoxNote note0{4, Position{19, 1}, Position{19, 1}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
   
    // final y is at y = 0. Board is a 20x20 board.
    PositionManager_Up upPositionManager(0, 0, 19, 0, 19);

    // futurePositions usually would contain positions {19, 0}, {18, 0}, {20, 0}.
    // Since the board's x only goes up to 19, futurePositions does not contain {20, 0}. 
    vector<Position> futurePositions = upPositionManager.getFuturePositions(box);
    for(Position futurePosition : futurePositions)
    {
        REQUIRE_FALSE(futurePosition == Position{20, 0});
    }
}

TEST_CASE("PositionManager_Up:: getFuturePositions doesn't return any positions that are off the board. Testing where box would have a next position with x smaller than zero.")
{
    // box is at Position{0, 1}.
    BoxNote note0{4, Position{0, 1}, Position{0, 1}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
   
    // final y is at y = 0. Board is a 20x20 board.
    PositionManager_Up upPositionManager(0, 0, 19, 0, 19);

    // futurePositions usually would contain positions {-1, 0}, {0, 0}, {1, 0}.
    // Since the board's smallest x is zero, futurePositions does not contain {-1, 0}. 
    vector<Position> futurePositions = upPositionManager.getFuturePositions(box);
    for(Position futurePosition : futurePositions)
    {
        REQUIRE_FALSE(futurePosition == Position{-1, 0});
    }
}


