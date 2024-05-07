#include "catch.hpp"
#include "../src/Drop.h"

using namespace std;

TEST_CASE("Drop_getters_setters::")
{
    SECTION("Drop Position is set in the constructor. Other attributes are set to default.")
    {
        Drop dropSimpleConstructor{10, 20};
        REQUIRE(Position{10, 20} == dropSimpleConstructor.getPosition());
        REQUIRE(-1 == dropSimpleConstructor.getBoxId());
        REQUIRE(SpotType::left == dropSimpleConstructor.getSpotType());
        REQUIRE(false == dropSimpleConstructor.hasChanged());
        
    }

    SECTION("Drop attributes set in advanced constructor.")
    {
        Drop dropAdvancedConstructor{10, 20, 1, SpotType::to_arrive};
        REQUIRE(Position{10, 20} == dropAdvancedConstructor.getPosition());
        REQUIRE(1 == dropAdvancedConstructor.getBoxId());
        REQUIRE(SpotType::to_arrive == dropAdvancedConstructor.getSpotType());
        REQUIRE_FALSE(dropAdvancedConstructor.hasChanged());
    }

    SECTION("set and get BoxId")
    {
        Drop drop{10, 20};
        drop.setBoxId(100);
        REQUIRE(100 == drop.getBoxId());
    }
    
    SECTION("set and get SpotType")
    {
        Drop drop{10, 20};
        drop.setSpotType(SpotType::to_leave);
        REQUIRE(SpotType::to_leave == drop.getSpotType());
    }
    
    SECTION("set and get hasChanged")
    {
        Drop drop{10, 20};
        drop.setHasChanged(true);
        REQUIRE(drop.hasChanged());
    }
        
}

