#include "catch.hpp"
#include "../src/PositionManager_Step.h"

using namespace std;

TEST_CASE("PositionManager_Step_core::")
{

    SECTION("atEnd() returns false if the given Position is not the final Position.")
    {
        PositionManager_Step pm{
            Position{5, 5}, 
            0,
            20,
            0,
            20};
        REQUIRE(false == pm.atEnd(Position{5, 4}));
        REQUIRE(false == pm.atEnd(Position{5, 6}));
        REQUIRE(false == pm.atEnd(Position{4, 5}));
        REQUIRE(false == pm.atEnd(Position{6, 5}));
    }

    SECTION("atEnd() returns true if given the Position is at final Position.")
    {
        PositionManager_Step pm{
        Position{5, 5}, 
        0,
        20,
        0,
        20};
        REQUIRE(true == pm.atEnd(Position{5, 5}));
    }

    // Target is north of original Position.
    SECTION("Target is at {0, 0}. Original Position is at {0, 10}. The Positions at index zero from calls to getFuturePositions() will be a straight line heading north.")
    {
        PositionManager_Step pm{
            Position{0, 0},
            0,
            21,
            0,
            21};
        Position currentPosition{0, 10};
        for(int ii=0; ii<10; ++ii)
        {
            currentPosition = pm.getFuturePositions(currentPosition)[0];
            REQUIRE(Position{0, 9-ii} == currentPosition);
        }
    }

    // Target is north east of original Position.
    SECTION("Target is at {5, 0}. Original Position is at {0, 25}. Slope (y/x) is -5. Every fifth call to getFuturePositions() will be on the line with x increased by 1 and y decreased by 5.")
    {
        PositionManager_Step pm{
            Position{5, 0},
            0,
            30,
            0,
            30};
        
        Position originalPosition{0, 25};
        Position currentPosition = originalPosition;
        Position requiredPosition = originalPosition;
        for(int ii=1; ii<=25; ++ii)
        {
            currentPosition = pm.getFuturePositions(currentPosition)[0];
            if (ii >= 5 && ii%5 == 0)
            {
                requiredPosition = Position{requiredPosition.getX()+1, requiredPosition.getY()-5};
                REQUIRE(requiredPosition == currentPosition);
            }
        }
    }

    // Target is east of original Position.
    SECTION("Target is at {10, 0}. Original Position is at {0, 0}. Calls to getFuturePositions are along the line heading east.")
    {
        PositionManager_Step pm{
            Position{10, 0},
            0,
            21,
            0,
            21};
        Position currentPosition{0, 0};
        for(int ii=1; ii<=10; ++ii)
        {
            currentPosition = pm.getFuturePositions(currentPosition)[0];
            REQUIRE(Position{ii, 0} == currentPosition);
        }
    }

    // Target is south east of original Position.
    SECTION("Target is at {5, 25}. Original Position is at {0, 0}. Slope (y/x) is 5. Every fifth call to getFuturePositions() will be on the line with x increased by 1 and y increased by 5.")
    {
        PositionManager_Step pm{
            Position{5, 25},
            0,
            30,
            0,
            30};
        
        Position originalPosition{0, 0};
        Position currentPosition = originalPosition;
        Position requiredPosition = originalPosition;
        for(int ii=1; ii<=25; ++ii)
        {
            currentPosition = pm.getFuturePositions(currentPosition)[0];
            if (ii >= 5 && ii%5 == 0)
            {
                requiredPosition = Position{requiredPosition.getX()+1, requiredPosition.getY()+5};
                REQUIRE(requiredPosition == currentPosition);
            }
        }
    }

    // Target is south of original Position.
    SECTION("Target is at {0, 10}. Original Position is at {0, 0}. Calls to getFuturePositions() are along the line heading south.")
    {
        PositionManager_Step pm{
            Position{0, 10},
            0,
            21,
            0,
            21};
        Position currentPosition{0, 0};
        for(int ii=1; ii<=10; ++ii)
        {
            currentPosition = pm.getFuturePositions(currentPosition)[0];
            REQUIRE(Position{0, ii} == currentPosition);
        }
    }

    // Target is south west of original Position.
    SECTION("Target is at {0, 25}. Original Position is at {5, 0}. Slope (y/x) is 5. Every fifth call to getFuturePositions() will be on the line with x decreased by 1 and y increased by 5.")
    {
        PositionManager_Step pm{
            Position{0, 25},
            0,
            30,
            0,
            30};
        
        Position originalPosition{5, 0};
        Position currentPosition = originalPosition;
        Position requiredPosition = originalPosition;
        for(int ii=1; ii<=25; ++ii)
        {
            currentPosition = pm.getFuturePositions(currentPosition)[0];
            if (ii >= 5 && ii%5 == 0)
            {
                requiredPosition = Position{requiredPosition.getX()-1, requiredPosition.getY()+5};
                REQUIRE(requiredPosition == currentPosition);
            }
        }
    }

    // Target is west of original Position.
    SECTION("Target is at {0, 0}. Original Position is at {10, 0}. Calls to getFuturePositions are along the line heading west.")
    {
        PositionManager_Step pm{
            Position{0, 0},
            0,
            21,
            0,
            21};
        Position currentPosition{10, 0};
        for(int ii=1; ii<=10; ++ii)
        {
            currentPosition = pm.getFuturePositions(currentPosition)[0];
            REQUIRE(Position{10-ii, 0} == currentPosition);
        }
    }

    // Target is north west of original Position.
    SECTION("Target is at {0, 0}. Original Position is at {5, 25}. Slope (y/x) is 5. Every fifth call to getFuturePositions() will be on the line with x decreased by 1 and y decreased by 5.")
    {
        PositionManager_Step pm{
            Position{0, 0},
            0,
            30,
            0,
            30};
        
        Position originalPosition{5, 25};
        Position currentPosition = originalPosition;
        Position requiredPosition = originalPosition;
        for(int ii=1; ii<=25; ++ii)
        {
            currentPosition = pm.getFuturePositions(currentPosition)[0];
            if (ii >= 5 && ii%5 == 0)
            {
                requiredPosition = Position{requiredPosition.getX()-1, requiredPosition.getY()-5};
                REQUIRE(requiredPosition == currentPosition);
            }
        }
    }

    SECTION("getFuturePositions() throws an exception if @position is off the Board.")
    {
        PositionManager_Step pm{
            Position{0, 0},
            0,
            30,
            0,
            30};

        REQUIRE_THROWS(pm.getFuturePositions(Position{31, 9}));
    }
    
    SECTION("getFuturePositions() returns an empty vector if @position is at the final target.")
    {
        PositionManager_Step pm{
            Position{0, 0},
            0,
            30,
            0,
            30};

        REQUIRE(vector<Position>{} == pm.getFuturePositions(Position{0, 0}));
    }
    
    SECTION("getEndRect() returns the final target as a Rectangle.")
    {
        PositionManager_Step pm{
            Position{6, 7},
            0,
            30,
            0,
            30};

        REQUIRE( Rectangle{Position{6, 7}, Position{6, 7}} == pm.getEndRect());
    }

    SECTION("getTargetRect() returns the final target as a Rectangle.")
    {
        PositionManager_Step pm{
            Position{6, 7},
            0,
            30,
            0,
            30};

        REQUIRE( Rectangle{Position{6, 7}, Position{6, 7}} == pm.getTargetRect());
    }

} // TEST_CASE("PositionManager_Step")
