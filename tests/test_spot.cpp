#include "catch.hpp"
#include <iostream>
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
    BoardNote note1{4, 1};
    BoardNote note2{4, 2};
    BoardNote note3{4, 3};

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
    BoardNote note1{4, 1};
    BoardNote note2{4, 2};
    BoardNote note3{3, 1};

    Spot spot{pos};
    spot.tagNote(note1);
    spot.tagNote(note2);
    spot.tagNote(note3);
    
    unordered_map<int, BoardNote> requiredNotes{};
    requiredNotes.insert({note2.getBoxId(), note2});
    REQUIRE(requiredNotes == spot.getNotes());
}

TEST_CASE("a 'type left' note will remove other type notes.")
{
    Position pos{3, 4};
    BoardNote note1{1, 1}; // box 1 to leave
    BoardNote note2{3, 1}; // box 1 left

    Spot spot{pos};

    spot.tagNote(note1);
    spot.tagNote(note2);
    REQUIRE(spot.getNotes().empty());

    BoardNote note3{2,1}; // box 1 to arrive
    spot.tagNote(note3);
    spot.tagNote(note2);
    REQUIRE(spot.getNotes().empty());

    BoardNote note4{4, 1}; // box 1 arrives
    spot.tagNote(note4);
    spot.tagNote(note2);
    REQUIRE(spot.getNotes().empty());
}

TEST_CASE("a 'type to leave' note will replace other types of notes")
{
    Position pos{3, 4};
    Spot spot{pos};
    
    BoardNote toLeaveNote{1, 1}; // box 1 to leave

    // Add a note, where box 1 is to arrive, that's type 2. Then add a note where box 1 is to leave, that's type 1.
    // Will result in returned notes having one pair {boxId 1, toLeaveNote}.
    BoardNote note1{2, 1}; // box 1 is to arrive
    spot.tagNote(note1);
    spot.tagNote(toLeaveNote);
    REQUIRE((spot.getNotes()).size() == 1); // map has a pair with box id equal to 1, and note is toLeaveNote. 
    REQUIRE(spot.getNotes().at(1) == toLeaveNote);

    // Clear notes in spot by adding a note with type 3, which is "left" note.
    spot.tagNote(BoardNote{3, 1}); 

    // Add a note, where box 1 arrives, that's type 4. Then add a note where box 1 is to leave, that's type 1.
    // Will result in returned notes having one pair {boxId 1, toLeaveNote}.
    BoardNote note2{4, 1}; // box 1 arrives
    spot.tagNote(note2);
    spot.tagNote(toLeaveNote);
    REQUIRE((spot.getNotes()).size() == 1); // map has a pair with box id equal to 1, and note is toLeaveNote. 
    REQUIRE(spot.getNotes().at(1) == toLeaveNote);
}

TEST_CASE("a 'type to arrive' note will replace other types of notes")
{
    Position pos{3, 4};
    Spot spot{pos};
    
    BoardNote toArriveNote{2, 1}; // box 1 to arrive 

    // Add a note, where box 1 is to leave, that's type 1. Then add a note where box 1 is to arrive, that's type 2.
    // Will result in returned notes having one pair {boxId 1, toArriveNote}.
    BoardNote note1{1, 1}; // box 1 is to leave 
    spot.tagNote(note1);
    spot.tagNote(toArriveNote);
    REQUIRE((spot.getNotes()).size() == 1); // map has a pair with box id equal to 1, and note is toLeaveNote. 
    REQUIRE(spot.getNotes().at(1) == toArriveNote);

    // Clear notes in spot by adding a note with type 3, which is "left" note.
    spot.tagNote(BoardNote{3, 1}); 

    // Add a note, where box 1 arrives, that's type 4. Then add a note where box 1 is to arrive, that's type 2.
    // Will result in returned notes having one pair {boxId 1, toArriveNote}.
    BoardNote note2{4, 1}; // box 1 arrives
    spot.tagNote(note2);
    spot.tagNote(toArriveNote);
    REQUIRE((spot.getNotes()).size() == 1); // map has a pair with box id equal to 1, and note is toArriveNote. 
    REQUIRE(spot.getNotes().at(1) == toArriveNote);
}

TEST_CASE("a 'type arrive' note will replace other types of notes")
{
    Position pos{3, 4};
    Spot spot{pos};
    
    BoardNote arriveNote{4, 1}; // box 1 arrive 

    // Add a note, where box 1 is to leave, that's type 1. Then add a note where box 1 is arriving, that's type 4.
    // Will result in returned notes having one pair {boxId 1, arriveNote}.
    BoardNote note1{1, 1}; // box 1 is to leave 
    spot.tagNote(note1);
    spot.tagNote(arriveNote);
    REQUIRE((spot.getNotes()).size() == 1); // map has a pair with box id equal to 1, and note is toLeaveNote. 
    REQUIRE(spot.getNotes().at(1) == arriveNote);

    // Clear notes in spot by adding a note with type 3, which is "left" note.
    spot.tagNote(BoardNote{3, 1}); 

    // Add a note, where box 1 is to arrive, that's type 2. Then add a note where box 1 arrives, that's type 4.
    // Will result in returned notes having one pair {boxId 1, arriveNote}.
    BoardNote note2{2, 1}; // box 1 toArrive 
    spot.tagNote(note2);
    spot.tagNote(arriveNote);
    REQUIRE((spot.getNotes()).size() == 1); // map has a pair with box id equal to 1, and note is arriveNote. 
    REQUIRE(spot.getNotes().at(1) == arriveNote);
}
