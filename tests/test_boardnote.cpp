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

TEST_CASE("BoardNote == operator returns true")
{
    BoardNote note1{1, 22};
    BoardNote note2{1, 22}; 
    REQUIRE(note1 == note2);
}

TEST_CASE("BoardNote == operator returns false if boxId's are different")
{
    BoardNote note1{1, 24};
    BoardNote note2{1, 22}; 
    REQUIRE_FALSE(note1 == note2);
}

TEST_CASE("BoardNote == operator returns false if type's are different")
{
    BoardNote note1{1, 22};
    BoardNote note2{2, 22}; 
    REQUIRE_FALSE(note1 == note2);
}
