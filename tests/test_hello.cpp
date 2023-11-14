#include "catch.hpp"
#include "../src/HelloWorld.h"

using namespace std;

TEST_CASE("Get back Hello World string")
{
    HelloWorld obj{};

    REQUIRE("Hello World" == obj.sayHello());
}
