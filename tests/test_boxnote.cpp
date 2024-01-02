#include "catch.hpp"

#include "../src/BoxNote.h"

using namespace std;

TEST_CASE("Returns type given in the constructor")
{
    Position toPos{4, 5};
    Position fromPos{7, 8};
    const std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    BoxNote boxNote{10, toPos, fromPos, now};
    REQUIRE(10 == boxNote.getType());
}

TEST_CASE("Returns fromPosition given in the constructor")
{
    Position toPos{4, 5};
    Position fromPos{7, 8};
    const std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    BoxNote boxNote{10, toPos, fromPos, now};
    REQUIRE(fromPos == boxNote.getFromPosition());
}

TEST_CASE("Returns toPosition given in the constructor")
{
    Position toPos{4, 5};
    Position fromPos{7, 8};
    const std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    BoxNote boxNote{10, toPos, fromPos, now};
    REQUIRE(toPos == boxNote.getToPosition());
}

TEST_CASE("Returns time point given in the contructor")
{
    Position toPos{4, 5};
    Position fromPos{7, 8};
    const std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    BoxNote boxNote{10, toPos, fromPos, now};
    
    REQUIRE(now == boxNote.getTimePoint());
}

TEST_CASE("Returns true if type, toPosition, fromPosition, and time stamp are equal")
{
    Position toPositionOne{1, 1};
    Position fromPositionOne{2, 2};
    const std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    BoxNote noteOne{10, toPositionOne, fromPositionOne, now};
    
    Position toPositionTwo{1, 1};
    Position fromPositionTwo{2, 2};
    BoxNote noteTwo{10, toPositionTwo, fromPositionTwo, now};

    REQUIRE(noteOne == noteTwo);
}

TEST_CASE("Returns false if type is different")
{
    Position toPositionOne{1, 1};
    Position fromPositionOne{2, 2};
    const std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    BoxNote noteOne{10, toPositionOne, fromPositionOne, now};

    BoxNote noteTwo{11, toPositionOne, fromPositionOne, now};

    REQUIRE_FALSE(noteOne == noteTwo);
}

TEST_CASE("Returns false if toPosition is different")
{
    Position toPositionOne{1, 1};
    Position fromPositionOne{2, 2};
    const std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    BoxNote noteOne{10, toPositionOne, fromPositionOne, now};

    
    Position toPositionTwo{2, 1};
    Position fromPositionTwo{2, 2};
    BoxNote noteTwo{10, toPositionTwo, fromPositionTwo, now};

    REQUIRE_FALSE(noteOne == noteTwo);
}
   
TEST_CASE("Returns false if fromPosition is different")
{
    Position toPositionOne{1, 1};
    Position fromPositionOne{2, 2};
    const std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    BoxNote noteOne{10, toPositionOne, fromPositionOne, now};

    
    Position toPositionTwo{1, 1};
    Position fromPositionTwo{3, 2};
    BoxNote noteTwo{10, toPositionTwo, fromPositionTwo, now};

    REQUIRE_FALSE(noteOne == noteTwo);
}

TEST_CASE("Returns false if time stamp is different")
{
    Position toPositionOne{1, 1};
    Position fromPositionOne{2, 2};
    const std::chrono::time_point<std::chrono::high_resolution_clock> now0 = std::chrono::high_resolution_clock::now();
    BoxNote noteOne{1, toPositionOne, fromPositionOne, now0};

    const std::chrono::time_point<std::chrono::high_resolution_clock> now1 = std::chrono::high_resolution_clock::now();
    BoxNote noteTwo{1, toPositionOne, fromPositionOne, now1};

    REQUIRE_FALSE(noteOne == noteTwo);
}
