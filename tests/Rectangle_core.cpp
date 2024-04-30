#include "catch.hpp"
#include "../src/Rectangle.h"

using namespace std;

TEST_CASE("Rectangle::core")
{

    SECTION("Bottom left corner and top right corner make a Rectangle.")
    {
        Rectangle rect{Position{100, 100}, Position{200, 50}};
        REQUIRE(Position{100, 50} == rect.getTopLeft());
        REQUIRE(Position{200, 100} == rect.getBottomRight());
    }

    SECTION("Top left corner and bottom right corner make a Rectangle.")
    {   
        Rectangle rect{Position{100, 50}, Position{100, 100}};
        REQUIRE(Position{100, 50} == rect.getTopLeft());
        REQUIRE(Position{100, 100} == rect.getBottomRight());
    }
}

