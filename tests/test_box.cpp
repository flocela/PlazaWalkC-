#include "catch.hpp"
#include "../src/Box.h"

using namespace std;

TEST_CASE("Box:: id is set in constructor")
{
    Box box{10, 1, 2};
    REQUIRE(10 == box.getId());
}

TEST_CASE("Box:: width and height is declared in the constructor")
{
    Box box{0, 8, 7};

    REQUIRE(7 == box.getHeight());
    REQUIRE(8 == box.getWidth());
}


TEST_CASE("Boxes with different ids are not equal '=='")
{
    Box boxA{0, 1, 2};
    Box boxB{5, 1, 2};    
    
    REQUIRE_FALSE(boxA == boxB);
}

TEST_CASE("Boxes with different heights are not equal '=='")
{
    Box boxA{0, 1, 2};
    Box boxB{0, 5, 2};    
    
    REQUIRE_FALSE(boxA == boxB);
}

TEST_CASE("Boxes with different widths are not equal '=='")
{
    Box boxA{0, 1, 2};
    Box boxB{0, 1, 5};    
    
    REQUIRE_FALSE(boxA == boxB);
}


TEST_CASE("hash function should return the ")
{
    // TODO need a hash function test!!!
}






