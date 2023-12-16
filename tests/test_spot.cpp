#include "catch.hpp"

#include "../src/Spot.h"

using namespace std;

TEST_CASE("returns Position")
{
    Position pos{3, 4};

    // BoardNote{type, boxId}
    BoardNote note1{1, 1};
    BoardNote note2{1, 3};
    BoardNote note3{1, 1};

    Spot spot{pos};
    spot.tagNote(note1);
    spot.tagNote(note2);
    spot.tagNote(note3);
    
    REQUIRE(pos == spot.getPosition());
}
    
TEST_CASE("returns notes that are in Spot, 3 arrivals")
{
    Position pos{3, 4};

    // BoardNote{type, boxId}
    BoardNote note1{1, 1};
    BoardNote note2{1, 2};
    BoardNote note3{1, 3};

    Spot spot{pos};
    spot.tagNote(note1);
    spot.tagNote(note2);
    spot.tagNote(note3);
    
    unordered_map<int, BoardNote> requiredNotes{};
    requiredNotes.insert({note1.getBoxId(), note1});
    requiredNotes.insert({note2.getBoxId(), note2});
    requiredNotes.insert({note3.getBoxId(), note3});

    REQUIRE(requiredNotes == spot.getNotes());
}

TEST_CASE("returns notes that are in Spot, 2 arrivals, 1 departure")
{
    Position pos{3, 4};
    BoardNote note1{1, 1};
    BoardNote note2{1, 2};
    BoardNote note3{2, 1};

    Spot spot{pos};
    spot.tagNote(note1);
    spot.tagNote(note2);
    spot.tagNote(note3);
    
    unordered_map<int, BoardNote> requiredNotes{};
    requiredNotes.insert({note2.getBoxId(), note2});
    REQUIRE(requiredNotes == spot.getNotes());
}
