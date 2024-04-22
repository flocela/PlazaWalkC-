#include "catch.hpp"
#include "../src/BoxInfo.h"
#include <thread>

using namespace std;

TEST_CASE("BoxInfo_core::")
{
    SECTION("Copy Constructor")
    {
        BoxInfo boxInfoA{0, 0, 1, 2, 3};
        BoxInfo boxInfoB{boxInfoA};    
        
        REQUIRE(boxInfoA == boxInfoB);
    }

    SECTION("Assigment Constructor")
    {
        BoxInfo boxInfoA{0, 0, 1, 2, 3};
        BoxInfo boxInfoB{std::move(boxInfoA)};
        
        REQUIRE(boxInfoA == boxInfoB);
    }

    SECTION("BoxInfos with different ids are not equal '=='")
    {
        BoxInfo boxInfoA{0, 0, 1, 2, 0};
        BoxInfo boxInfoB{5, 0, 1, 2, 0};    
        
        REQUIRE_FALSE(boxInfoA == boxInfoB);
    }

    SECTION("BoxInfos with different heights are not equal '=='")
    {
        BoxInfo boxInfoA{0, 0, 1, 2, 0};
        BoxInfo boxInfoB{0, 0, 5, 2, 0};    
        
        REQUIRE_FALSE(boxInfoA == boxInfoB);
    }

    SECTION("BoxInfos with different widths are not equal '=='")
    {
        BoxInfo boxInfoA{0, 0, 1, 2, 0};
        BoxInfo boxInfoB{0, 0, 1, 5, 0};    
        
        REQUIRE_FALSE(boxInfoA == boxInfoB);
    }

    SECTION("BoxInfos with same id, group, width, height, and level are '=='")
    {
        BoxInfo boxInfoA{0, 0, 1, 2, 3};
        BoxInfo boxInfoB{0, 0, 1, 2, 3};    
        
        REQUIRE(boxInfoA == boxInfoB);
    }

    SECTION("BoxInfos with different levels are not equal '=='")
    {
        BoxInfo boxInfoA{0, 0, 1, 2, 3};
        BoxInfo boxInfoB{0, 0, 1, 2, 4};    
        
        REQUIRE_FALSE(boxInfoA == boxInfoB);
    }
}
