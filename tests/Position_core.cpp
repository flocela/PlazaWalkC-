#include "catch.hpp"
#include "../src/Position.h"

#include <iostream>
#include <sstream>

using namespace std;

TEST_CASE("Position_core::")
{
    SECTION("construct a position")
    {
        Position p{10, 12};
        
        REQUIRE(p.getX() == 10);
        REQUIRE(p.getY() == 12);
    }

    SECTION("print position")
    {
        Position p{1000, 1200};
       
        ostringstream oss;
        oss << p; 
        REQUIRE(oss.str() == "[1000, 1200]");
    }

    SECTION("operator == when x is different")
    {
        Position p{10, 12};
        Position op{1000, 12};
        
        REQUIRE_FALSE(p == op);
    }

    SECTION("operator == when y is different")
    {
        Position p{10, 12};
        Position op{10, 1200};
        
        REQUIRE_FALSE(p == op);
    }

    SECTION("operator == when positions are equal")
    {
        Position p{10, 12};
        Position op{10, 12};
        
        REQUIRE(p == op);
    }

    SECTION("toString()")
    {
        Position p{101, 202};
        REQUIRE("[101, 202]" == p.toString());
    }
}
