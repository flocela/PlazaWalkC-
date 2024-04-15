#include "catch.hpp"
#include "../src/Util.h"

using namespace std;

TEST_CASE("Returns numbers in the range [0, 100]")
{
    vector<int> randomInts = Util::getRandom(0, 100, 1000);
    for(int x : randomInts)
    {
        REQUIRE(((x >= 0) && (x<= 100)));
    }
}

TEST_CASE("Returns count number of ints")
{
    vector<int> randomInts = Util::getRandom(0, 100, 1000);
    REQUIRE(1000 == randomInts.size());
}

TEST_CASE("Returns Positions that are in the rectangle outlined by the given corners")
{
    vector<Position> insideRectangle = Util::getRandomInRectangle(Position{0, 100}, Position{100, 0}, 1000);
    
    for(Position pos : insideRectangle)
    {
        REQUIRE(((pos.getX() >= 0) && (pos.getX() <= 100)));
        REQUIRE(((pos.getY() >= 0) && (pos.getY() <= 100)));
    }
}

TEST_CASE("Returns count number of Positions")
{
    vector<Position> insideRectangle = Util::getRandomInRectangle(Position{0, 100}, Position{100, 0}, 1000);
    REQUIRE(1000 == insideRectangle.size());
}
// TODO move to MainSetup Tests
/*
TEST_CASE("Returns a vector of boxes with 10 groups, each of size 5")
{
    vector<Box> boxes = Util::getBoxes(100, 10, 5);
    for(int ii=0; ii<boxes.size(); ++ii)
    {
        REQUIRE(boxes[ii] == Box{100 + ii, ii%10, 3, 3});
    }
}
*/
