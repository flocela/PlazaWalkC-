#include "catch.hpp"
#include "../src/Box.h"
#include <thread>

using namespace std;

TEST_CASE("Copy Constructor")
{
    Box boxA{0, 0, 1, 2};
    Box boxB{boxA};    
    
    REQUIRE(boxA == boxB);
}

TEST_CASE("Assigment Constructor")
{
    Box boxA{0, 0, 1, 2};
    Box boxB{std::move(boxA)};
    
    REQUIRE(boxA == boxB);
}

TEST_CASE("Boxes with different ids are not equal '=='")
{
    Box boxA{0, 0, 1, 2};
    Box boxB{5, 0, 1, 2};    
    
    REQUIRE_FALSE(boxA == boxB);
}

TEST_CASE("Boxes with different heights are not equal '=='")
{
    Box boxA{0, 0, 1, 2};
    Box boxB{0, 0, 5, 2};    
    
    REQUIRE_FALSE(boxA == boxB);
}

TEST_CASE("Boxes with different widths are not equal '=='")
{
    Box boxA{0, 0, 1, 2};
    Box boxB{0, 0, 1, 5};    
    
    REQUIRE_FALSE(boxA == boxB);
}

TEST_CASE("Boxes with same id, group, width, and height are '=='")
{
    Box boxA{0, 0, 1, 2};
    Box boxB{0, 0, 1, 2};    
    
    REQUIRE(boxA == boxB);
}

TEST_CASE("Boxes with different levels are equal '=='")
{
    Box boxA{0, 0, 1, 2};
    Box boxB{0, 0, 1, 2};    
    boxA.upLevel();
    
    REQUIRE(boxA == boxB);
}

TEST_CASE("Box gives the correct BoxInfo when getInfo() is called")
{
    Box boxA{10, 10, 3, 3};
    boxA.upLevel();
    REQUIRE(BoxInfo{10, 10, 3, 3, 1} == boxA.getInfo());
}
