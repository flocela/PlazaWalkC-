#include "catch.hpp"
#include "../src/SpotType.h"

#include <sstream>
#include <string>

using namespace std;

TEST_CASE("output to ostream")
{
    stringstream ss{};
    ss << SpotType::to_arrive;
    REQUIRE(ss.str() == "to_arrive");

    ss.str(string());
    ss << SpotType::arrive;
    REQUIRE(ss.str() == "arrive");
    
    ss.str(string());
    ss << SpotType::to_leave;
    REQUIRE(ss.str() == "to_leave");

    ss.str(string());
    ss << SpotType::left;
    REQUIRE(ss.str() == "left");
}
