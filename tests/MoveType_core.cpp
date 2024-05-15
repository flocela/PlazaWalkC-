#include "catch.hpp"
#include "../src/MoveType.h"

#include <sstream>

using namespace std;

TEST_CASE("MoveType_core::")
{

    SECTION("ostream operator prints correct type.")
    {
        stringstream ss;
        
        ss << MoveType::to_arrive;
        REQUIRE("MoveType::to_arrive" == ss.str());

        ss.str(std::string());
        ss << MoveType::arrive;
        REQUIRE("MoveType::arrive" == ss.str());

        ss.str(std::string());
        ss << MoveType::to_leave;
        REQUIRE("MoveType::to_leave" == ss.str());

        ss.str(std::string());
        ss << MoveType::left;
        REQUIRE("MoveType::left" == ss.str());

    }
}
