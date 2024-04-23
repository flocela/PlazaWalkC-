#include "catch.hpp"
#include "../src/Drop.h"

using namespace std;

TEST_CASE("Drop_core::")
{
    SECTION("Copy Constructor")
    {
        Drop dropA{10, 11, 5, SpotType::to_arrive};
        dropA.setHasChanged(true); 
        Drop dropB{dropA};    
        
        REQUIRE(dropA == dropB);
    }

    SECTION("Assigment Constructor")
    {
        Drop dropA{10, 11, 5, SpotType::to_arrive};
        dropA.setHasChanged(true); 
        Drop dropB{std::move(dropA)};
        
        REQUIRE(dropA == dropB);
    }

    SECTION("Drops with different positions are not equal '=='.")
    {
        Drop drop{10, 11, 5, SpotType::to_arrive};
        drop.setHasChanged(true); 

        Drop dropDiffX{100, 11, 5, SpotType::to_arrive};
        dropDiffX.setHasChanged(true); 

        Drop dropDiffY{10, 110, 5, SpotType::to_arrive};
        dropDiffY.setHasChanged(true); 
        
        REQUIRE_FALSE(drop == dropDiffX);
        REQUIRE_FALSE(drop == dropDiffY);
    }

    SECTION("Drops with different SpotTypes are equal '=='.")
    {
        Drop drop{10, 11, 5, SpotType::to_arrive};
        drop.setHasChanged(true); 

        Drop dropDiffType{10, 11, 5, SpotType::arrive};
        dropDiffType.setHasChanged(true);

        REQUIRE(drop == dropDiffType);
    }

    SECTION("Drops with different hasChanged are equal '=='.")
    {
        Drop drop{10, 11, 5, SpotType::to_arrive};
        drop.setHasChanged(true); 

        Drop dropDiffHasChanged{10, 11, 5, SpotType::arrive};
        dropDiffHasChanged.setHasChanged(false);

        REQUIRE(drop == dropDiffHasChanged);
    }

    SECTION("Drops that are the same are equal '=='.")
    {
        Drop drop{10, 11, 5, SpotType::to_arrive};
        drop.setHasChanged(true); 

        Drop dropSame{10, 11, 5, SpotType::arrive};
        dropSame.setHasChanged(true);

        REQUIRE(drop == dropSame);
    }
}
