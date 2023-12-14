#include "catch.hpp"

#include "../src/BoardNote.h"

using namespace std;

TEST_CASE("BoardNote returns type")
{
    BoardNote note{1, 22};
    REQUIRE(1 == note.getType());
}

TEST_CASE("BoardNote returns boxId")
{
    BoardNote note{1, 22};
    REQUIRE(22 == note.getBoxId());
}
