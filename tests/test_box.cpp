#include "catch.hpp"
#include "../src/Box.h"

using namespace std;

TEST_CASE("Box:: id is set in constructor")
{
    Box box{10, 1, 2};
    REQUIRE(10 == box.getId());
}

TEST_CASE("Box:: change width and height")
{
    Box box{0, 8, 7};

    REQUIRE(7 == box.getHeight());
    REQUIRE(8 == box.getWidth());
    
    box.setHeight(4);
    box.setWidth(3);

    REQUIRE(4 == box.getHeight());
    REQUIRE(3 == box.getWidth());
}

TEST_CASE("Box Returns the notes that were added to it.")
{
    BoxNote note0{0, Position{1,1}, Position{2,1}};
    BoxNote note1{1, Position{1,1}, Position{2,1}};
    BoxNote note2{2, Position{1,1}, Position{2,1}};
    BoxNote note3{3, Position{1,1}, Position{2,1}};
    BoxNote note4{4, Position{1,1}, Position{2,1}};
    BoxNote note5{5, Position{2,1}, Position{3,1}};
    BoxNote note6{6, Position{2,1}, Position{3,1}};
    BoxNote note7{7, Position{2,1}, Position{3,1}};
    BoxNote note8{8, Position{2,1}, Position{3,1}};
    BoxNote note9{9, Position{3,1}, Position{4,1}};
    BoxNote note10{10, Position{3,1}, Position{4,1}};

    Box box{0, 10, 10};
    box.addNote(note0);
    box.addNote(note1);
    box.addNote(note2);
    box.addNote(note3);
    box.addNote(note4);
    box.addNote(note5);
    box.addNote(note6);
    box.addNote(note7);
    box.addNote(note8);
    box.addNote(note9);
    box.addNote(note10);

    vector<BoxNote> expectedNotes{};
    expectedNotes.push_back(note0);
    expectedNotes.push_back(note1);
    expectedNotes.push_back(note2);
    expectedNotes.push_back(note3);
    expectedNotes.push_back(note4);
    expectedNotes.push_back(note5);
    expectedNotes.push_back(note6);
    expectedNotes.push_back(note7);
    expectedNotes.push_back(note8);
    expectedNotes.push_back(note9);
    expectedNotes.push_back(note10);

    REQUIRE(expectedNotes == box.getAllNotes());
}

TEST_CASE("Box returns last 4 notes.")
{
    BoxNote note0{0, Position{1,1}, Position{2,1}};
    BoxNote note1{1, Position{1,1}, Position{2,1}};
    BoxNote note2{2, Position{1,1}, Position{2,1}};
    BoxNote note3{3, Position{1,1}, Position{2,1}};
    BoxNote note4{4, Position{1,1}, Position{2,1}};
    BoxNote note5{5, Position{2,1}, Position{3,1}};
    BoxNote note6{6, Position{2,1}, Position{3,1}};
    BoxNote note7{7, Position{2,1}, Position{3,1}};
    BoxNote note8{8, Position{2,1}, Position{3,1}};
    BoxNote note9{9, Position{3,1}, Position{4,1}};
    BoxNote note10{10, Position{3,1}, Position{4,1}};

    Box box{0, 10, 10};
    box.addNote(note0);
    box.addNote(note1);
    box.addNote(note2);
    box.addNote(note3);
    box.addNote(note4);
    box.addNote(note5);
    box.addNote(note6);
    box.addNote(note7);
    box.addNote(note8);
    box.addNote(note9);
    box.addNote(note10);

    vector<BoxNote> expectedNotes{};
    expectedNotes.push_back(note7);
    expectedNotes.push_back(note8);
    expectedNotes.push_back(note9);
    expectedNotes.push_back(note10);

    REQUIRE(expectedNotes == box.getLastNotes(4));
}
TEST_CASE("Boxes with different ids are not equal '=='")
{
    Box boxA{0, 1, 2};
    Box boxB{5, 1, 2};    
    
    REQUIRE_FALSE(boxA == boxB);
}

TEST_CASE("Boxes with different heights are not equal '=='")
{
    Box boxA{0, 1, 2};
    Box boxB{0, 5, 2};    
    
    REQUIRE_FALSE(boxA == boxB);
}

TEST_CASE("Boxes with different widths are not equal '=='")
{
    Box boxA{0, 1, 2};
    Box boxB{0, 1, 5};    
    
    REQUIRE_FALSE(boxA == boxB);
}

TEST_CASE("hash function should return the ")
{
    // TODO need a hash function test!!!
}






