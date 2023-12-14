#include "catch.hpp"

#include "../src/BoxNote.h"

using namespace std;

TEST_CASE("Returns correct type")
{
    Position toPos{4, 5};
    Position fromPos{7, 8};
    BoxNote boxNote{1, toPos, fromPos};
    REQUIRE(1 == boxNote.getType());
}

TEST_CASE("Returns correct fromPosition")
{
    Position toPos{4, 5};
    Position fromPos{7, 8};
    BoxNote boxNote{1, toPos, fromPos};
    REQUIRE(fromPos == boxNote.getFromPosition());
}

TEST_CASE("Returns correct toPosition")
{
    Position toPos{4, 5};
    Position fromPos{7, 8};
    BoxNote boxNote{1, toPos, fromPos};
    REQUIRE(toPos == boxNote.getToPosition());
}
