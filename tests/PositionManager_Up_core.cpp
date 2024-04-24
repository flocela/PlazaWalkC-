#include "catch.hpp"
#include "../src/PositionManager_Up.h"

using namespace std;

TEST_CASE("PositionManager_Up_core::")
{
    // Box is moving up. If Current position is Position(a, b), then first position is Position(a, b-1). Corresponding to moving up. Second position is Position(a-1, b). Third position is Position(a+1, b).
   SECTION("Should return next positions, which are: up, right, and left.")
    {
        PositionManager_Up upPositionManager{0, 0, 10, 0, 10};
        vector<Position> positions = upPositionManager.getFuturePositions(Position{5, 5});
        REQUIRE(positions.size() == 3);
        REQUIRE(positions[0] == Position{5, 4}); 
        REQUIRE(positions[1] == Position{6, 5});
        REQUIRE(positions[2] == Position{4, 5});
    }

    SECTION("PositionManager_Up::atEnd() returns true if box has reached its final position.")
    {
        PositionManager_Up upPositionManager(1, 0, 10, 0, 10);
        REQUIRE(true == upPositionManager.atEnd(Position{5, 1}));
    }

    SECTION("PositionManager_Up::atEnd() returns true if box is above the final position.")
    {
        PositionManager_Up upPositionManager(1, 0, 10, 0, 10);
        REQUIRE(true == upPositionManager.atEnd(Position{5, 0}));
    }

    SECTION("PositionManager_Up::atEnd() returns false if box is below its final position.")
    {
        PositionManager_Up upPositionManager(1, 0, 10, 0, 10);
        REQUIRE(false == upPositionManager.atEnd(Position{5, 2}));
    }

    SECTION("PositionManager_Up:: box's current position is already at end, then getFuturePositions returns an empty vector.")
    {
        // final y is at y = 0. Board is a 20x20 board.
        PositionManager_Up upPositionManager{0, 0, 19, 0, 19};
        REQUIRE(vector<Position>{} == upPositionManager.getFuturePositions(Position{5, 0}));
    }

    SECTION("PositionManager_Up:: getFuturePositions doesn't return any positions that are off the board. Current position is at the right edge. It does not return a position with an x of 20, that would be off the board")
    {
        // final y is at y = 0. Board is a 20x20 board.
        PositionManager_Up upPositionManager(0, 0, 19, 0, 19);

        // futurePositions usually would contain positions {19, 0}, {18, 1}, {20, 1}.
        // Since the board's x only goes up to 19, futurePositions does not contain {20, 1}. 
        vector<Position> futurePositions = upPositionManager.getFuturePositions(Position{19, 1});
        for(Position futurePosition : futurePositions)
        {
            REQUIRE(futurePosition.getX() <= 19);
        }
    }

    SECTION("PositionManager_Up:: getFuturePositions doesn't return any positions that are off the board. Current position is at the left edge. It does not return a position with an x less than zero, that would be off the board.")
    {
        // final y is at y = 0. Board is a 20x20 board.
        PositionManager_Up upPositionManager(0, 0, 19, 0, 19);

        // futurePositions usually would contain positions {0, 0}, {-1, 1}, {1, 1}.
        // Since the board's smallest x is zero, futurePositions does not contain {-1, 0}. 
        vector<Position> futurePositions = upPositionManager.getFuturePositions(Position{0, 1});
        for(Position futurePosition : futurePositions)
        {
            REQUIRE(futurePosition.getX() >= 0);
        }
    }
}

