#include "catch.hpp"
#include "../src/SpotType.h"

#include <sstream>

using namespace std;

TEST_CASE("SpotType_core::")
{

    SECTION("ostream operator prints correct type.")
    {
        stringstream ss;
        
        ss << SpotType::to_arrive;
        REQUIRE("SpotType::to_arrive" == ss.str());

        ss.str(std::string());
        ss << SpotType::arrive;
        REQUIRE("SpotType::arrive" == ss.str());

        ss.str(std::string());
        ss << SpotType::to_leave;
        REQUIRE("SpotType::to_leave" == ss.str());

        ss.str(std::string());
        ss << SpotType::left;
        REQUIRE("SpotType::left" == ss.str());

    }
}
