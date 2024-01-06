#include "catch.hpp"
#include "../src/BoardCallback.h"
#include "../src/Board.h"
#include <iostream>

using namespace std;

TEST_CASE("Adding a BoardNote to the board results in a message being added to the BoardCallback object.")
{
    // BoardNotes from box 0
    BoardNote box0NoteType2{2, 0}; // box 0 is about to arrive
    BoardNote box0NoteType4{4, 0}; // box 0 arrives

    Board board{10, 10};

    Position pos0{5, 5};

    BoardCallback callbackForPos0{};
    board.registerCallback(pos0, callbackForPos0);
    
    // box0 arrives at pos0.
    board.addNote(pos0, box0NoteType2);
    board.addNote(pos0, box0NoteType4);
    
    // callbackForPos0 index 0 has a map of size 1, with box0Note2.
    REQUIRE( 1 == callbackForPos0.getNotes().at(0).second.size() );
    REQUIRE( box0NoteType2 == callbackForPos0.getNotes().at(0).second.at(0) );
    
    // callbackForPos0 index 1 has a map of size 1, with box0Note4.
    REQUIRE( 1 == callbackForPos0.getNotes().at(1).second.size() );
    REQUIRE( box0NoteType4 == callbackForPos0.getNotes().at(1).second.at(0) );
}

TEST_CASE("Add board notes for the case where a box moves from start position to end position. Two positions should have all the board notes in order.")
{
    // BoardNotes from box 0
    BoardNote box0NoteType2{2, 0}; // box 0 is about to arrive
    BoardNote box0NoteType4{4, 0}; // box 0 arrives

    // BoardNotes from box 1
    BoardNote box1NoteType1{1, 1}; // box 1 is about to leave
    BoardNote box1NoteType2{2, 1}; // box 1 is about to arrive
    BoardNote box1NoteType3{3, 1}; // box 1 has left
    BoardNote box1NoteType4{4, 1}; // box 1 arrives

    Board board{10, 10};

    Position pos0{5, 5};
    Position pos1{5, 6};

    BoardCallback callbackForPos0{};
    BoardCallback callbackForPos1{};
    board.registerCallback(pos0, callbackForPos0);
    board.registerCallback(pos1, callbackForPos1);

    // box0 arrives at pos0.
    board.addNote(pos0, box0NoteType2);
    board.addNote(pos0, box0NoteType4);
   
    // box1 arrives at pos0. 
    board.addNote(pos0, box1NoteType4);

    // box1 is about to arrive in pos1.
    board.addNote(pos1, box1NoteType2);

    // box1 is about to leave pos0.
    board.addNote(pos0, box1NoteType1);

    // box1 has arrived in pos1
    board.addNote(pos1, box1NoteType4);

    // box1 has left pos0
    board.addNote(pos0, box1NoteType3);

    // callbackForPos0 index 0 has a map of size 1, with box0Note2.
    REQUIRE( 1 == callbackForPos0.getNotes().at(0).second.size() );
    REQUIRE( box0NoteType2 == callbackForPos0.getNotes().at(0).second.at(0) );

    // callbackForPos0 index 1 has a map of size 1, with box0Note4.
    REQUIRE( 1 == callbackForPos0.getNotes().at(1).second.size() );
    REQUIRE( box0NoteType4 == callbackForPos0.getNotes().at(1).second.at(0) );

    // callbackForPos0 index 2 has a map of size 2, with box0Note4 and box1Note4.
    REQUIRE( 2 == callbackForPos0.getNotes().at(2).second.size() );
    REQUIRE( box0NoteType4 == callbackForPos0.getNotes().at(2).second.at(0) );
    REQUIRE( box1NoteType4 == callbackForPos0.getNotes().at(2).second.at(1) );

    // callbackForPos1 index 0 has a map of size 1, with box1Note2.
    REQUIRE( 1 == callbackForPos1.getNotes().at(0).second.size() );
    REQUIRE( box1NoteType2 == callbackForPos1.getNotes().at(0).second.at(1) );
    
    // callbackForPos0 index 3 has a map of size 2, with box0Note4 and box1Note1.
    REQUIRE( 2 == callbackForPos0.getNotes().at(3).second.size() );
    REQUIRE( box0NoteType4 == callbackForPos0.getNotes().at(3).second.at(0) );
    REQUIRE( box1NoteType1 == callbackForPos0.getNotes().at(3).second.at(1) );
    
    // callbackForPos1 index 1 has a map of size 1, with box1Note4.
    REQUIRE( 1 == callbackForPos1.getNotes().at(1).second.size() );
    REQUIRE( box1NoteType4 == callbackForPos1.getNotes().at(1).second.at(1) );
    
    // callbackForPos0 index 4 has a map of size 1, with box0Note4.
    REQUIRE( 1 == callbackForPos0.getNotes().at(4).second.size() );
    REQUIRE( box0NoteType4 == callbackForPos0.getNotes().at(4).second.at(0) );
}
