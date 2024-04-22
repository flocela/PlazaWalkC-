#include "catch.hpp"
#include "../src/Board.h"

using namespace std;

TEST_CASE("Board_getters_setters::")
{
    SECTION("getHeight() and getWidth() return the Board's dimensions")
    {
        Board board{20, 10, vector<Box>{}};
        REQUIRE(board.getHeight() == 10);
        REQUIRE(board.getWidth() == 20); 
    }
}
