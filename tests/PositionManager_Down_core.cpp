#include "catch.hpp"
#include "../src/PositionManager_Down.h"

using namespace std;

TEST_CASE("PositionManger_Down_core::")
{
    // Box is moving down. If Current position is Position(a, b), then 
    // first position is Position(a, b+1). Corresponding to moving down.
    // second position is Position(a-1, b). Corresponding to mvoing left.
    // third  position is Position(a+1, b). Corresponding to moving right.
    SECTION("When getFututePositions() is called, should return the following positions in this order: straight down, left, right")
    {
        // PositionManager_Down{finalY, boardMinX, boardMaxX, boardMinY, boardMaxY}
        PositionManager_Down downPositionManager{10, 0, 10, 0, 10};

        vector<Position> positions = downPositionManager.getFuturePositions(Position{5, 5});
        REQUIRE(3 == positions.size());
        REQUIRE(positions[0] == Position{5, 6});
        REQUIRE(positions[1] == Position{4, 5});
        REQUIRE(positions[2] == Position{6, 5});
    }

    SECTION("PositionManager_Down::atEnd() returns true if box reached the final Y position.")
    {
        // PositionManager_Down{finalY, boardMinX, boardMaxX, boardMinY, boardMaxY}
        PositionManager_Down downPositionManager(1, 0, 10, 0, 10);
        REQUIRE(true == downPositionManager.atEnd(Position{1, 1}));
    }

    SECTION("PositionManager_Down::atEnd() returns false if box has not reached the final Y position.")
    {
        // PositionManager_Down{finalY, boardMinX, boardMaxX, boardMinY, boardMaxY}
        PositionManager_Down downPositionManager(1, 0, 10, 0, 10);
        REQUIRE(false == downPositionManager.atEnd(Position{0, 0}));
    }

    SECTION("PositionManager_Down::atEnd() returns true if box is past the final Y position.")
    {   
        // PositionManager_Down{finalY, boardMinX, boardMaxX, boardMinY, boardMaxY}
        PositionManager_Down downPositionManager(1, 0, 10, 0, 10);
        REQUIRE(true == downPositionManager.atEnd(Position{2, 2}));
    }

    SECTION("box's current position is already at end, then getFuturePositions returns an empty vector.")
    {
        // PositionManager_Down{finalY, boardMinX, boardMaxX, boardMinY, boardMaxY}
        PositionManager_Down downPositionManager{10, 0, 19, 0, 19};
        REQUIRE(vector<Position>{} == downPositionManager.getFuturePositions(Position{10, 10}));
    }

    SECTION("getFuturePositions doesn't return any positions that are off the board. Current position is at the right edge of the board. getFuturePosition does not return a postion with an x of 20, that would be off the board.")
    {
        // final y is at y = 10. Board is a 20x20 board.
        // PositionManager_Down{finalY, boardMinX, boardMaxX, boardMinY, boardMaxY}
        PositionManager_Down downPositionManager(10, 0, 19, 0, 19);

        // futurePositions usually would contain positions {19, 10}, {18, 9}, {20, 9}.
        // Since the board's x only goes up to 19, futurePositions does not contain {20, 9}. 
        vector<Position> futurePositions = downPositionManager.getFuturePositions(Position{19, 9});
        for(Position futurePosition : futurePositions)
        {
            REQUIRE(futurePosition.getX() <= 19);
        }
    }

    SECTION("getFuturePositions doesn't return any positions that are off the board. Current position is at the left edge of the board. getFuturePosition does not return a position with an x of -1, that would be off the board.")
    {
        // final y is at y = 10. Board is a 20x20 board.
        PositionManager_Down downPositionManager(10, 0, 19, 0, 19);

        // futurePositions usually would contain positions {0, 9}, {-1, 8}, {1, 8}.
        // Since the board's smallest x is zero, futurePositions does not contain {-1, 10}. 
        vector<Position> futurePositions = downPositionManager.getFuturePositions(Position{0, 8});

        for(Position futurePosition : futurePositions)
        {
            REQUIRE(futurePosition.getX() >= 0);
        }
    }
}
