#include "catch.hpp"
#include "../src/BoardReader_Reg.h"

using namespace std;

TEST_CASE("getHeight() and getWidth() returns the contained Board's dimensions")
{
    Board board{20, 10};
    
    BoardReader_Reg boardReader{board};

    REQUIRE(boardReader.getHeight() == 10);
    REQUIRE(boardReader.getWidth() == 20); 
}

TEST_CASE("addNotes to board and get them out using BoardReader_Reg. 3 arrivals")
{   
    // BoardNote(int type, int boxId)
    BoardNote note1{4, 11};
    BoardNote note2{4, 12};
    BoardNote note3{4, 13};
    Board board{20, 10};

    BoardReader_Reg boardReader{board};
    
    board.addNote(Position{1,1}, note1);
    board.addNote(Position{1,1}, note2);
    board.addNote(Position{1,1}, note3);

    unordered_map<int, BoardNote> expectedNotes{};
    expectedNotes.insert({11, note1}); 
    expectedNotes.insert({12, note2}); 
    expectedNotes.insert({13, note3}); 

    REQUIRE( expectedNotes ==  boardReader.getNotes(Position{1,1}) );
}

TEST_CASE("addNotes to board and get them out using BoardReader_Reg. 2 arrivals and 1 departure")
{   
    // BoardNote(int type, int boxId)
    BoardNote note1{4, 11};
    BoardNote note2{4, 12};
    BoardNote note3{3, 11};
    Board board{20, 10};

    BoardReader_Reg boardReader{board};

    board.addNote(Position{1,1}, note1);
    board.addNote(Position{1,1}, note2);
    board.addNote(Position{1,1}, note3);

    unordered_map<int, BoardNote> expectedNotes{};
    expectedNotes.insert({12, note2}); 

    REQUIRE( expectedNotes ==  boardReader.getNotes(Position{1,1}) );
}
