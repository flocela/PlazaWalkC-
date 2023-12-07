#include "catch.hpp"
#include "../src/Box.h"

using namespace std;

TEST_CASE("Box:: id is set in constructor")
{
    Box box{10, 1, 2, 3, 4};
    REQUIRE(10 == box.getId());
}


TEST_CASE("Box:: change x and y positions")
{
    Box box{1, 7, 8, 8, 9};

    REQUIRE(8 == box.getX());
    REQUIRE(9 == box.getY());
    
    box.setX(3);
    box.setY(4);

    REQUIRE(3 == box.getX());
    REQUIRE(4 == box.getY());
}

TEST_CASE("Box:: change width and height")
{
    Box box{0, 8, 7, 8, 9};

    REQUIRE(7 == box.getHeight());
    REQUIRE(8 == box.getWidth());
    
    box.setHeight(4);
    box.setWidth(3);

    REQUIRE(4 == box.getHeight());
    REQUIRE(3 == box.getWidth());
}

TEST_CASE("Boxes with different ids are not equal '=='")
{
    Box boxA{0, 1, 2, 3, 4};
    Box boxB{5, 1, 2, 3, 4};    
    
    REQUIRE_FALSE(boxA == boxB);
}

TEST_CASE("Boxes with different heights are not equal '=='")
{
    Box boxA{0, 1, 2, 3, 4};
    Box boxB{0, 5, 2, 3, 4};    
    
    REQUIRE_FALSE(boxA == boxB);
}

TEST_CASE("Boxes with different widths are not equal '=='")
{
    Box boxA{0, 1, 2, 3, 4};
    Box boxB{0, 1, 5, 3, 4};    
    
    REQUIRE_FALSE(boxA == boxB);
}

TEST_CASE("Boxes with different xPos are not equal '=='")
{
    Box boxA{0, 1, 2, 3, 4};
    Box boxB{0, 1, 2, 5, 4};    
    
    REQUIRE_FALSE(boxA == boxB);
}

TEST_CASE("Boxes with different yPos are not equal '=='")
{
    Box boxA{0, 1, 2, 3, 4};
    Box boxB{0, 1, 2, 3, 5};    
    
    REQUIRE_FALSE(boxA == boxB);
}

TEST_CASE("hash function should return the ")
{
    // TODO need a hash function test!!!
}






