#include "catch.hpp"
#include "../src/PositionManager_Up.h"

using namespace std;

TEST_CASE("PositionManager_Up_core::")
{
    // Box is moving up. If Current Position is Position(a, b), then first Position is Position(a, b-1). Corresponding to moving up. Second Position is Position(a-1, b). Third Position is Position(a+1, b).
   SECTION("Should return next Positions, which are: up, right, and left.")
    {
        PositionManager_Up upPositionManager{0, 0, 10, 0, 10};
        vector<Position> positions = upPositionManager.getFuturePositions(Position{5, 5});
        REQUIRE(positions.size() == 3);
        REQUIRE(positions[0] == Position{5, 4}); 
        REQUIRE(positions[1] == Position{6, 5});
        REQUIRE(positions[2] == Position{4, 5});
    }

    SECTION("PositionManager_Up::atEnd() returns true if box has reached its final Position.")
    {
        PositionManager_Up upPositionManager(1, 0, 10, 0, 10);
        REQUIRE(true == upPositionManager.atEnd(Position{5, 1}));
    }

    SECTION("PositionManager_Up::atEnd() returns true if box is above the final Position.")
    {
        PositionManager_Up upPositionManager(1, 0, 10, 0, 10);
        REQUIRE(true == upPositionManager.atEnd(Position{5, 0}));
    }

    SECTION("PositionManager_Up::atEnd() returns false if box is below its final Position.")
    {
        PositionManager_Up upPositionManager(1, 0, 10, 0, 10);
        REQUIRE(false == upPositionManager.atEnd(Position{5, 2}));
    }

    SECTION("PositionManager_Up:: box's current Position is already at end, then getFuturePositions returns an empty vector.")
    {
        // final y is at y = 0. Board is a 20x20 board.
        PositionManager_Up upPositionManager{0, 0, 19, 0, 19};
        REQUIRE(vector<Position>{} == upPositionManager.getFuturePositions(Position{5, 0}));
    }

    SECTION("PositionManager_Up:: getFuturePositions doesn't return any Positions that are off the board. Current Position is at the right edge. It does not return a Position with an x of 20, that would be off the board")
    {
        // final y is at y = 0. Board is a 20x20 board.
        PositionManager_Up upPositionManager(0, 0, 19, 0, 19);

        // futurePositions usually would contain Positions {19, 0}, {18, 1}, {20, 1}.
        // Since the board's x only goes up to 19, futurePositions does not contain {20, 1}. 
        vector<Position> futurePositions = upPositionManager.getFuturePositions(Position{19, 1});
        for(Position futurePosition : futurePositions)
        {
            REQUIRE(futurePosition.getX() <= 19);
        }
    }

    SECTION("PositionManager_Up:: getFuturePositions doesn't return any Positions that are off the board. Current Position is at the left edge. It does not return a Position with an x less than zero, that would be off the board.")
    {
        // final y is at y = 0. Board is a 20x20 board.
        PositionManager_Up upPositionManager(0, 0, 19, 0, 19);

        // futurePositions usually would contain Positions {0, 0}, {-1, 1}, {1, 1}.
        // Since the board's smallest x is zero, futurePositions does not contain {-1, 0}. 
        vector<Position> futurePositions = upPositionManager.getFuturePositions(Position{0, 1});
        for(Position futurePosition : futurePositions)
        {
            REQUIRE(futurePosition.getX() >= 0);
        }
    }

    SECTION("getFuturePositions() throws an exception if @position is off the Board.")
    {
        // final y is at y = 10. Board is a 20x20 board.
        PositionManager_Up pm(10, 0, 19, 0, 19);

        REQUIRE_THROWS(pm.getFuturePositions(Position{20, 9}));
    }
        
    SECTION("getFuturePositions() returns an empty vector if @position is at or above final Y.")
    {
        // final y is at y = 10. Board is a 20x20 board.
        PositionManager_Up pm(10, 0, 19, 0, 19);

        REQUIRE(vector<Position>{} == pm.getFuturePositions(Position{1, 9}));
        REQUIRE(vector<Position>{} == pm.getFuturePositions(Position{1, 10}));
    }

    SECTION("getEndRect() returns a horizontal Rectangle at final Y with a width of the Board and a height of zero.")
    {
        // final y is at y = 10. Board is a 20x20 board.
        PositionManager_Up pm(10, 0, 19, 0, 19);
        REQUIRE(Rectangle{Position{0, 10}, Position{19, 10}} == pm.getEndRect());
    }

    SECTION("getTargetRect() returns a horizontal Rectangle at final Y with a width of the Board and a height of zero.")
    {
        // final y is at y = 10. Board is a 20x20 board.
        PositionManager_Up pm(10, 0, 19, 0, 19);
        REQUIRE(Rectangle{Position{0, 10}, Position{19, 10}} == pm.getTargetRect());
    }
}

