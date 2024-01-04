#include "catch.hpp"
#include "../src/BoardChanger_Reg.h"

using namespace std;

TEST_CASE("addNotes to boardChanger adds notes to contained board. 3 arrivals")
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

TEST_CASE("addNotes to boardChanger adds notes to contained board. 2 arrivals and 1 departure")
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


