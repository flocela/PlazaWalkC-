#include "catch.hpp"
#include "../src/Box.h"
#include <thread>

using namespace std;

void funcUpLevel(Box& box)
{
    for(int ii=0; ii<1000; ++ii)
    {
        box.upLevel();
    }
}

TEST_CASE("Box::threads")
{
    // To force this test to fail, comment out the unique_lock in the upLevel() method.
    SECTION("Two threads repeatedly try to change Box's level, but because of Box's unique_lock in upLevel(), one thread always waits for the other one to finish")
    {
        Box box{0, 0, 2, 2};
        
        std::thread t1(funcUpLevel, std::ref(box));
        std::thread t2(funcUpLevel, std::ref(box));
       
        t1.join();
        t2.join();

        // Since each thread is allowed to complete its level up before the next thread begins its
        // level up, the box's final level will be 2000. One thousand level ups from t1 and one thousand
        // level ups from t2.
        REQUIRE(2000 == box.getLevel());
    }

    // getInfo() has a shared lock, which does not allow getInfo() to access _level while it is 
    // being changed in the upLevel() method, which is protected by getLevel(). This isn't tested,
    // but true by definition.

    SECTION("hash function should return the ")
    {
        // TODO need a hash function test!!!
    }
}
