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

TEST_CASE("Returns true if type, toPosition, and fromPosition are equal")
{
    Position toPositionOne{1, 1};
    Position fromPositionOne{2, 2};
    BoxNote noteOne{1, toPositionOne, fromPositionOne};

    
    Position toPositionTwo{1, 1};
    Position fromPositionTwo{2, 2};
    BoxNote noteTwo{1, toPositionTwo, fromPositionTwo};

    REQUIRE(noteOne == noteTwo);
}

TEST_CASE("Returns false if type is different")
{
    Position toPositionOne{1, 1};
    Position fromPositionOne{2, 2};
    BoxNote noteOne{1, toPositionOne, fromPositionOne};

    
    Position toPositionTwo{1, 1};
    Position fromPositionTwo{2, 2};
    BoxNote noteTwo{2, toPositionTwo, fromPositionTwo};

    REQUIRE_FALSE(noteOne == noteTwo);
}

TEST_CASE("Returns false if toPosition is different")
{
    Position toPositionOne{1, 1};
    Position fromPositionOne{2, 2};
    BoxNote noteOne{1, toPositionOne, fromPositionOne};

    
    Position toPositionTwo{2, 1};
    Position fromPositionTwo{2, 2};
    BoxNote noteTwo{1, toPositionTwo, fromPositionTwo};

    REQUIRE_FALSE(noteOne == noteTwo);
}
   
TEST_CASE("Returns false if fromPosition is different")
{
    Position toPositionOne{1, 1};
    Position fromPositionOne{2, 2};
    BoxNote noteOne{1, toPositionOne, fromPositionOne};

    
    Position toPositionTwo{1, 1};
    Position fromPositionTwo{3, 2};
    BoxNote noteTwo{1, toPositionTwo, fromPositionTwo};

    REQUIRE_FALSE(noteOne == noteTwo);
}
