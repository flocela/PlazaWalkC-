#include "catch.hpp"
#include "../src/Box.h"

using namespace std;

TEST_CASE("Box:: id is set in constructor")
{
    Box box{10, 1, 2};
    REQUIRE(10 == box.getId());
}


TEST_CASE("Box:: width and height is declared in the constructor")
{
    Box box{0, 8, 7};

    REQUIRE(7 == box.getHeight());
    REQUIRE(8 == box.getWidth());
}

TEST_CASE("Box Returns the notes that were added to it.")
{
    std::chrono::time_point<std::chrono::high_resolution_clock> timeStamp = std::chrono::high_resolution_clock::now();
    BoxNote note0{10, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note1{11, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note2{10, Position{3,1}, Position{1,1}, timeStamp};
    BoxNote note3{11, Position{3,1}, Position{1,1}, timeStamp};
    BoxNote note4{10, Position{4,1}, Position{3,1}, timeStamp};
    BoxNote note5{11, Position{4,1}, Position{3,1}, timeStamp};

    Box box{0, 10, 10};
    box.addNote(note0);
    box.addNote(note1);
    box.addNote(note2);
    box.addNote(note3);
    box.addNote(note4);
    box.addNote(note5);

    vector<BoxNote> expectedNotes{};
    expectedNotes.push_back(note0);
    expectedNotes.push_back(note1);
    expectedNotes.push_back(note2);
    expectedNotes.push_back(note3);
    expectedNotes.push_back(note4);
    expectedNotes.push_back(note5);

    REQUIRE(expectedNotes == box.getAllNotes());
}

TEST_CASE("Box returns last 4 notes.")
{
    std::chrono::time_point<std::chrono::high_resolution_clock> timeStamp = std::chrono::high_resolution_clock::now();
    BoxNote note0{10, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note1{11, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note2{10, Position{3,1}, Position{1,1}, timeStamp};
    BoxNote note3{11, Position{3,1}, Position{1,1}, timeStamp};
    BoxNote note4{10, Position{4,1}, Position{3,1}, timeStamp};
    BoxNote note5{11, Position{4,1}, Position{3,1}, timeStamp};

    Box box{0, 10, 10};
    box.addNote(note0);
    box.addNote(note1);
    box.addNote(note2);
    box.addNote(note3);
    box.addNote(note4);
    box.addNote(note5);
    
    vector<BoxNote> expectedNotes{};
    expectedNotes.push_back(note2);
    expectedNotes.push_back(note3);
    expectedNotes.push_back(note4);
    expectedNotes.push_back(note5);

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

TEST_CASE("getPos() returns last arrive position before given timestamp")
{
    Box box{0, 10, 10};
    
    // First boxNote with type 11 which is the arrive type.
    BoxNote boxNote0{11, Position{0,0}, Position{0,0}, std::chrono::high_resolution_clock::now()};
    box.addNote(boxNote0);
   
    // boxNote1 with type 10 is a "to leave" type.
    BoxNote boxNote1{10, Position{1,0}, Position{0,0}, std::chrono::high_resolution_clock::now()};
    box.addNote(boxNote1);

    BoxNote boxNote2{11, Position{1,0}, Position{0,0}, std::chrono::high_resolution_clock::now()};
    box.addNote(boxNote2);

    BoxNote boxNote3{10, Position{1,1}, Position{1,0}, std::chrono::high_resolution_clock::now()};
    box.addNote(boxNote3);
    
    BoxNote boxNote4{11, Position{1,1}, Position{1,0}, std::chrono::high_resolution_clock::now()};
    box.addNote(boxNote4);

    // Cut off time
    std::chrono::time_point<std::chrono::high_resolution_clock> cutOffTime =
        std::chrono::high_resolution_clock::now();

    BoxNote boxNote5{10, Position{2,1}, Position{1,1}, std::chrono::high_resolution_clock::now()};
    box.addNote(boxNote5);

    BoxNote boxNote6{4, Position{2,1}, Position{1,1}, std::chrono::high_resolution_clock::now()};
    box.addNote(boxNote6);

    REQUIRE(Position{1,1} == box.getPos(cutOffTime));

}


TEST_CASE("hash function should return the ")
{
    // TODO need a hash function test!!!
}






