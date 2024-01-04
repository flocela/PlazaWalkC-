#include "catch.hpp"
#include "../src/Board.h"

#include <memory>
#include <unordered_set>
#include <iostream>
using namespace std;

TEST_CASE("getHeight() and getWidth() return the Board's dimensions")
{
    Board board{20, 10};
    REQUIRE(board.getHeight() == 10);
    REQUIRE(board.getWidth() == 20); 
}

TEST_CASE("addNotes to board and get them out. 3 arrivals")
{   
    // BoardNote(int type, int boxId)
    BoardNote note1{4, 11};
    BoardNote note2{4, 12};
    BoardNote note3{4, 13};
    Board board{20, 10};
    
    board.addNote(Position{1,1}, note1);
    board.addNote(Position{1,1}, note2);
    board.addNote(Position{1,1}, note3);

    unordered_map<int, BoardNote> expectedNotes{};
    expectedNotes.insert({11, note1}); 
    expectedNotes.insert({12, note2}); 
    expectedNotes.insert({13, note3}); 

    REQUIRE( expectedNotes ==  board.getNotes(Position{1,1}) );
}

TEST_CASE("addNotes to board and get them out. 2 arrivals and 1 departure")
{   
    // BoardNote(int type, int boxId)
    BoardNote note1{4, 11};
    BoardNote note2{4, 12};
    BoardNote note3{3, 11};
    Board board{20, 10};
    
    board.addNote(Position{1,1}, note1);
    board.addNote(Position{1,1}, note2);
    board.addNote(Position{1,1}, note3);

    unordered_map<int, BoardNote> expectedNotes{};
    expectedNotes.insert({12, note2}); 

    REQUIRE( expectedNotes ==  board.getNotes(Position{1,1}) );
}

TEST_CASE("addNotes in order of BoardNote types 2:toArrive, 4:arrive, 1:toLeave, 3:left")
{
    BoardNote noteType2{2, 0}; 
    BoardNote noteType4{4, 0};
    BoardNote noteType1{1, 0};
    BoardNote noteType3{3, 0};

    Board board{10, 10};
    Position pos{5, 5};
    
    board.addNote(pos, noteType2);
    REQUIRE( 1 == board.getNotes(pos).size() );
    REQUIRE( noteType2 == board.getNotes(pos).at(0) );

    board.addNote(pos, noteType4);
    REQUIRE( 1 == board.getNotes(pos).size() );
    REQUIRE( noteType4 == board.getNotes(pos).at(0) );

    board.addNote(pos, noteType1);
    REQUIRE( 1 == board.getNotes(pos).size() );
    REQUIRE( noteType1 == board.getNotes(pos).at(0) );

    board.addNote(pos, noteType3);
    REQUIRE( 0 == board.getNotes(pos).size() );
}

TEST_CASE("addNotes in order of BoardNote types 2:toArrive, 4:arrive, 1:toLeave, 3:left from two boxes")
{
    // BoardNotes from box 0
    BoardNote box0NoteType2{2, 0}; 
    BoardNote box0NoteType4{4, 0};
    BoardNote box0NoteType1{1, 0};
    BoardNote box0NoteType3{3, 0};

    // BoardNotes from box 1
    BoardNote box1NoteType2{2, 1};
    BoardNote box1NoteType4{4, 1};

    Board board{10, 10};
    Position pos{5, 5};

    board.addNote(pos, box1NoteType2);
    board.addNote(pos, box1NoteType4);
    
    board.addNote(pos, box0NoteType2);
    REQUIRE( 2 == board.getNotes(pos).size() );
    REQUIRE( box0NoteType2 == board.getNotes(pos).at(0) );
    REQUIRE( box1NoteType4 == board.getNotes(pos).at(1) );

    board.addNote(pos, box0NoteType4);
    REQUIRE( 2 == board.getNotes(pos).size() );
    REQUIRE( box0NoteType4 == board.getNotes(pos).at(0) );
    REQUIRE( box1NoteType4 == board.getNotes(pos).at(1) );

    board.addNote(pos, box0NoteType1);
    REQUIRE( 2 == board.getNotes(pos).size() );
    REQUIRE( box0NoteType1 == board.getNotes(pos).at(0) );
    REQUIRE( box1NoteType4 == board.getNotes(pos).at(1) );

    board.addNote(pos, box0NoteType3);
    REQUIRE( 1 == board.getNotes(pos).size() );
    REQUIRE( box1NoteType4 == board.getNotes(pos).at(1) );
}
