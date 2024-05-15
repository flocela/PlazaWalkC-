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
        REQUIRE(MoveType::left == dropSimpleConstructor.getMoveType());
        REQUIRE(false == dropSimpleConstructor.hasChanged());
        
    }

    SECTION("Drop attributes set in advanced constructor.")
    {
        Drop dropAdvancedConstructor{10, 20, 1, MoveType::to_arrive};
        REQUIRE(Position{10, 20} == dropAdvancedConstructor.getPosition());
        REQUIRE(1 == dropAdvancedConstructor.getBoxId());
        REQUIRE(MoveType::to_arrive == dropAdvancedConstructor.getMoveType());
        REQUIRE_FALSE(dropAdvancedConstructor.hasChanged());
    }

    SECTION("set and get BoxId")
    {
        Drop drop{10, 20};
        drop.setBoxId(100);
        REQUIRE(100 == drop.getBoxId());
    }
    
    SECTION("set and get MoveType")
    {
        Drop drop{10, 20};
        drop.setMoveType(MoveType::to_leave);
        REQUIRE(MoveType::to_leave == drop.getMoveType());
    }
    
    SECTION("set and get hasChanged")
    {
        Drop drop{10, 20};
        drop.setHasChanged(true);
        REQUIRE(drop.hasChanged());
    }
        
}

