#include "catch.hpp"
#include "../src/Box.h"
#include <thread>

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

TEST_CASE("Box:: level initially zero")
{
    Box box{0, 8, 7};

    REQUIRE(0 == box.getLevel());
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

TEST_CASE("Boxes with different levels are equal '=='")
{
    Box boxA{0, 1, 2};
    Box boxB{0, 1, 2};    
    boxA.upLevel();
    
    REQUIRE(boxA == boxB);
}

void funcUpLevel(Box& box)
{
    for(int ii=0; ii<1000; ++ii)
    {
        box.upLevel();
    }
}

// To force this test to fail, comment out the unique_lock in the upLevel() method.
TEST_CASE("Two threads repeatedly trying to change Box's level, but because of Box's unique_lock in upLevel(), one thread always waits for the other one to finish")
{
    Box box{0, 2, 2};
    
    std::thread t1(funcUpLevel, std::ref(box));
    std::thread t2(funcUpLevel, std::ref(box));
   
    t1.join();
    t2.join();

    REQUIRE(2000 == box.getLevel());
}

TEST_CASE("One thread repeately calls Box's upLevel() function, the main thread repeatedly reads the Box's level. The box's level never goes down.")
{
    Box box{0, 2, 2};
    int level = box.getLevel();
    std::thread t1(funcUpLevel, std::ref(box));
    for(int ii=0; ii<1000; ++ii)
    {
        REQUIRE( (level <= box.getLevel()) );
        level = box.getLevel();
    }
    t1.join();
}

TEST_CASE("hash function should return the ")
{
    // TODO need a hash function test!!!
}






