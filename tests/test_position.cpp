#include "catch.hpp"

#include "../src/Position.h"

using namespace std;

TEST_CASE("construct a position")
{
    Position p{10, 12};
    
    REQUIRE(p.getX() == 10);
    REQUIRE(p.getY() == 12);
}
