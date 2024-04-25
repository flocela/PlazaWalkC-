#include "catch.hpp"
#include "../src/Color.h"

using namespace std;

vector<vector<uint8_t>> purple{
{0xF3, 0xE5, 0xF5},
{0xE1, 0xBE, 0xE7},
{0xCE, 0x93, 0xD8},
{0xBA, 0x68, 0xC8},
{0xAB, 0x47, 0xBC},
{0x9C, 0x27, 0xB0},
{0x8E, 0x24, 0xAA},
{0x7B, 0x1F, 0xA2},
{0x6A, 0x1B, 0x9A},
{0x4A, 0x14, 0x8C},
};

TEST_CASE("Color_core::")
{
    Color violet(purple);

    SECTION("Returns the correct red portion for the given level.")
    {
        REQUIRE(purple[2][0] == violet.getRed(2));
    }
    
    SECTION("Returns the correct green portion for the given level.")
    {
        REQUIRE(purple[5][1] == violet.getGreen(5));
    }
    
    SECTION("Returns the correct blue portion for the given level.")
    {
        REQUIRE(purple[0][2] == violet.getBlue(0));
    }

    SECTION("Returns the correct number of shades.")
    {
        REQUIRE(10 == violet.getNumberOfShades());
    } 
}

