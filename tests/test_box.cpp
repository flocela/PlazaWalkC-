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
    BoxNote note0{0, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note1{1, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note2{2, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note3{3, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note4{4, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note5{5, Position{2,1}, Position{3,1}, timeStamp};
    BoxNote note6{6, Position{2,1}, Position{3,1}, timeStamp};
    BoxNote note7{7, Position{2,1}, Position{3,1}, timeStamp};
    BoxNote note8{8, Position{2,1}, Position{3,1}, timeStamp};
    BoxNote note9{9, Position{3,1}, Position{4,1}, timeStamp};
    BoxNote note10{10, Position{3,1}, Position{4,1}, timeStamp};

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
    std::chrono::time_point<std::chrono::high_resolution_clock> timeStamp = std::chrono::high_resolution_clock::now();
    BoxNote note0{0, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note1{1, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note2{2, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note3{3, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note4{4, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note5{5, Position{2,1}, Position{3,1}, timeStamp};
    BoxNote note6{6, Position{2,1}, Position{3,1}, timeStamp};
    BoxNote note7{7, Position{2,1}, Position{3,1}, timeStamp};
    BoxNote note8{8, Position{2,1}, Position{3,1}, timeStamp};
    BoxNote note9{9, Position{3,1}, Position{4,1}, timeStamp};
    BoxNote note10{10, Position{3,1}, Position{4,1}, timeStamp};

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

TEST_CASE("getPos() returns last arrive position before given timestamp")
{
    Box box{0, 10, 10};
    
    // First boxNote with type 4 which is the arrive type.
    BoxNote boxNote0{4, Position{0,0}, Position{0,0}, std::chrono::high_resolution_clock::now()};
    box.addNote(boxNote0);
    
    BoxNote boxNote1{1, Position{1,0}, Position{0,0}, std::chrono::high_resolution_clock::now()};
    box.addNote(boxNote1);

    BoxNote boxNote2{2, Position{1,0}, Position{0,0}, std::chrono::high_resolution_clock::now()};
    box.addNote(boxNote2);

    // Second boxNote with type 4 which is the arrive type. Should return this toPostion, Position{1, 0}
    BoxNote boxNote3{4, Position{1,0}, Position{0,0}, std::chrono::high_resolution_clock::now()};
    box.addNote(boxNote3);
    
    BoxNote boxNote4{1, Position{2,0}, Position{1,0}, std::chrono::high_resolution_clock::now()};
    box.addNote(boxNote4);

    // Cut off time
    std::chrono::time_point<std::chrono::high_resolution_clock> cutOffTime =
        std::chrono::high_resolution_clock::now();

    BoxNote boxNote5{2, Position{2,0}, Position{1,0}, std::chrono::high_resolution_clock::now()};
    box.addNote(boxNote5);

    // Third boxNote with type 4 which is the arrive type. Doesn't matter because its past the cut off time.
    BoxNote boxNote6{4, Position{2,0}, Position{1,0}, std::chrono::high_resolution_clock::now()};
    box.addNote(boxNote6);

    REQUIRE(Position{1,0} == box.getPos(cutOffTime));

}
    


TEST_CASE("hash function should return the ")
{
    // TODO need a hash function test!!!
}






