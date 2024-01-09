#include "catch.hpp"
#include "../src/PositionManager_Down.h"

using namespace std;

// box is moving down. If Current position is Position(a, b), then 
//      first position is Position(a, b+1). Corresponding to moving down.
//      second position is Position(a-1, b+1).
//      third position is Position(a+1, b+1).
TEST_CASE("Should return next positions, which are down, then the diagonal position down and right, then the diagonal position down and left.")
{
    // note0's type is 4, which means it arrives at Position(5, 5);
    BoxNote note0{4, Position{5, 5}, Position{5, 4}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
    box.addNote(note0);

    PositionManager_Down downPositionManager{10, 0, 10, 0, 10};
    vector<Position> positions = downPositionManager.getFuturePositions(box);
    REQUIRE(positions[0] == Position{5, 6});
    REQUIRE(positions[1] == Position{4, 6});
    REQUIRE(positions[2] == Position{6, 6});

}

TEST_CASE(" PositionManager_Down::atEnd() returns true if box has reached its final position.")
{
    // box has arrived at Position{1, 1}.    
    BoxNote note0{4, Position{1, 1}, Position{1, 1}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
    box.addNote(note0);
    PositionManager_Down downPositionManager(1, 0, 10, 0, 10);
    REQUIRE(true == downPositionManager.atEnd(box));
}

TEST_CASE(" PositionManager_Down::atEnd() returns false if box is not at its final position.")
{
    // box has arrived at Position{0, 0}.    
    BoxNote note0{4, Position{0, 0}, Position{0, 0}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
    box.addNote(note0);
    PositionManager_Down downPositionManager(1, 0, 10, 0, 10);
    REQUIRE(false == downPositionManager.atEnd(box));
}

TEST_CASE("box's current position is already at end, then getFuturePositions returns an empty vector.")
{
    // box is at Position{10, 10}.
    BoxNote note0{4, Position{10, 10}, Position{10, 10}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
    box.addNote(note0);
   
    // final y is at y = 10. Board is a 20x20 board.
    PositionManager_Down downPositionManager{10, 0, 19, 0, 19};
    REQUIRE(vector<Position>{} == downPositionManager.getFuturePositions(box));
}

TEST_CASE("getFuturePositions doesn't return any positions that are off the board. Testing where box would have a next position larger than board.size()-1")
{
    // box is at Position{19, 9}.
    BoxNote note0{4, Position{19, 9}, Position{19, 9}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
    box.addNote(note0);
   
    // final y is at y = 10. Board is a 20x20 board.
    PositionManager_Down downPositionManager(10, 0, 19, 0, 19);

    // futurePositions usually would contain positions {19, 10}, {18, 10}, {20, 10}.
    // Since the board's x only goes up to 19, futurePositions does not contain {20, 10}. 
    vector<Position> futurePositions = downPositionManager.getFuturePositions(box);
    for(Position futurePosition : futurePositions)
    {
        REQUIRE_FALSE(futurePosition == Position{20, 10});
    }
}

TEST_CASE("getFuturePositions doesn't return any positions that are off the board. Testing where box would have a next position smaller than zero.")
{
    // box is at Position{0, 9}.
    BoxNote note0{4, Position{0, 9}, Position{0, 9}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
    box.addNote(note0);
   
    // final y is at y = 10. Board is a 20x20 board.
    PositionManager_Down downPositionManager(10, 0, 19, 0, 19);

    // futurePositions usually would contain positions {-1, 10}, {0, 10}, {1, 10}.
    // Since the board's smallest x is zero, futurePositions does not contain {-1, 10}. 
    vector<Position> futurePositions = downPositionManager.getFuturePositions(box);
    for(Position futurePosition : futurePositions)
    {
        REQUIRE_FALSE(futurePosition == Position{-1, 10});
    }
}
