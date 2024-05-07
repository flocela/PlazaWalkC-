#include "catch.hpp"
#include "../src/Box.h"

using namespace std;

TEST_CASE("Box_getters_setters::")
{
    SECTION("id is set in constructor")
    {
        Box box{10, 0, 1, 2};
        REQUIRE(10 == box.getId());
    }

    SECTION("group is set in constructor")
    {
        Box box{10, 12, 1, 2};
        REQUIRE(12 == box.getGroupId());
    }

    SECTION("width and height are declared in the constructor")
    {
        Box box{0, 0, 8, 7};

        REQUIRE(7 == box.getHeight());
        REQUIRE(8 == box.getWidth());
    }

    SECTION("Box:: level initially zero")
    {
        Box box{0, 0, 8, 7};

        REQUIRE(0 == box.getLevel());
    }
}
