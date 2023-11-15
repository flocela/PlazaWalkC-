#include "catch.hpp"
#include "../src/Box.h"

using namespace std;

TEST_CASE("Box:: change x and y positions")
{
    Box box{7, 8, 8, 9};

    REQUIRE(8 == box.getX());
    REQUIRE(9 == box.getY());
    
    box.setX(3);
    box.setY(4);

    REQUIRE(3 == box.getX());
    REQUIRE(4 == box.getY());
}

TEST_CASE("Box:: change width and height")
{
    Box box{7, 8, 8, 9};

    REQUIRE(7 == box.getHeight());
    REQUIRE(8 == box.getWidth());
    
    box.setHeight(4);
    box.setWidth(3);

    REQUIRE(4 == box.getHeight());
    REQUIRE(3 == box.getWidth());
}


