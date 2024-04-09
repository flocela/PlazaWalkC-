#include "catch.hpp"
#include "../src/PositionManager_Slide.h"

using namespace std;

TEST_CASE("PositionManager_Slide::")
{

SECTION(" atEnd() returns false if given position is not final position.")
{
    PositionManager_Slide pm{
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

SECTION(" atEnd() returns true if given position is at final position.")
{
    PositionManager_Slide pm{
    Position{5, 5}, 
    0,
    20,
    0,
    20};
    REQUIRE(true == pm.atEnd(Position{5, 5}));
}

SECTION(" getEndPoint() returns the final position.")
{
    PositionManager_Slide pm{
        Position{5, 5}, 
        0,
        20,
        0,
        20};
    REQUIRE(Position{5, 5} == pm.getEndPoint().first);
    REQUIRE(Position{5, 5} == pm.getEndPoint().second);
}

SECTION(" Say a box starts at original position. The line from original position to final target has a slope of 4. Using the first position given from calls to getFuturePositions() will result in the box being positioned on the line every 4th call.")
{
    PositionManager_Slide pm{
        Position{5, 20},
        0,
        21,
        0,
        21};
    Position currentPosition{0, 0};
    for(int ii=0; ii<4; ++ii)
    {
        currentPosition = pm.getFuturePositions(currentPosition)[0];
    }
    REQUIRE(Position{1, 4} == currentPosition);
    for(int ii=0; ii<4; ++ii)
    {
        currentPosition = pm.getFuturePositions(currentPosition)[0];
    }
    REQUIRE(Position{2, 8} == currentPosition);
}

} // TEST_CASE("PositionManager_Slide")
