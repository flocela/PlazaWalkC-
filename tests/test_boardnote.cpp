#include "catch.hpp"

#include "../src/BoardNote.h"

using namespace std;

TEST_CASE("BoardNote returns type")
{
    BoardNote note{22, 1};
    REQUIRE(1 == note.getType());
}

TEST_CASE("BoardNote returns boxId")
{
    BoardNote note{22, 4};
    REQUIRE(22 == note.getBoxId());
}

TEST_CASE("BoardNote == operator returns true")
{
    BoardNote note1{22, 1};
    BoardNote note2{22, 1}; 
    REQUIRE(note1 == note2);
}

TEST_CASE("BoardNote == operator returns false if boxId's are different")
{
    BoardNote note1{22, 1};
    BoardNote note2{24, 1}; 
    REQUIRE_FALSE(note1 == note2);
}

TEST_CASE("BoardNote == operator returns false if type's are different")
{
    BoardNote note1{22, 1};
    BoardNote note2{22, 2}; 
    REQUIRE_FALSE(note1 == note2);
}
