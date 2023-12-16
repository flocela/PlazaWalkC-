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
    BoardNote note1{1, 11};
    BoardNote note2{1, 12};
    BoardNote note3{1, 13};
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
    BoardNote note1{1, 11};
    BoardNote note2{1, 12};
    BoardNote note3{2, 11};
    Board board{20, 10};
    
    board.addNote(Position{1,1}, note1);
    board.addNote(Position{1,1}, note2);
    board.addNote(Position{1,1}, note3);

    unordered_map<int, BoardNote> expectedNotes{};
    expectedNotes.insert({12, note2}); 

    REQUIRE( expectedNotes ==  board.getNotes(Position{1,1}) );
}
