#include "catch.hpp"
#include "../src/BoardCallback.h"
#include "../src/Board.h"

TEST_CASE("Add board notes for the case where a box moves from start position to end position. Two positions should have all the board notes in order.")
{
    // BoardNotes from box 0
    BoardNote box0NoteType1{1, 0}; // box 0 is about to leave
    BoardNote box0NoteType2{2, 0}; // box 0 is about to arrive
    BoardNote box0NoteType3{3, 0}; // box 0 has left
    BoardNote box0NoteType4{4, 0}; // box 0 arrives

    // BoardNotes from box 1
    BoardNote box1NoteType2{2, 1}; // box 1 is about to arrive
    BoardNote box1NoteType4{4, 1}; // box 1 arrives

    Board board{10, 10};

    Position pos0{5, 5};
    Position pos1{5, 6};

    BoardCallback callBackForPos0{};
    BoardCallback callBackForPos1{};
    board.registerCallback(pos0, callBackForPos0);
    board.registerCallback(pos1, callBackForPos1);

    // box1 arrives at pos0.
    board.addNote(pos0, box1NoteType2);
    board.addNote(pos0, box1NoteType4);
   
    // box0 arrives at pos0. 
    board.addNote(pos0, box0NoteType4);

    // box0 is about to arrive in pos1.
    board.addNote(pos1, box0NoteType2);

    // box0 is about to leave pos0.
    board.addNote(pos0, box0NoteType1);

    // box0 has arrived in pos1
    board.addNote(pos1, box0NoteType4);

    // box0 has left pos0
    board.addNote(pos0, box0NoteType3);

    // Pos0Callback index 0 has a map of size 1, with box1Note2.
    REQUIRE( 1 == callBackForPos0.getNotes().at(0).second.size() );
    REQUIRE( box1NoteType2 == callBackForPos0.getNotes().at(0).second.at(1) );
/*
    // Pos0Callback index 1 has a map of size 1, with box1Note4.
    REQUIRE( 1 == callBackForPos0.getNotes().at().second.size() );
    REQUIRE( box1NoteType4 == board.getNotes(pos).at(1) );

    
    REQUIRE( 2 == board.getNotes(pos).size() );
    REQUIRE( box0NoteType4 == board.getNotes(pos).at(0) );
    REQUIRE( box1NoteType4 == board.getNotes(pos).at(1) );

    REQUIRE( 2 == board.getNotes(pos).size() );
    REQUIRE( box0NoteType1 == board.getNotes(pos).at(0) );
    REQUIRE( box1NoteType4 == board.getNotes(pos).at(1) );
*/
}
