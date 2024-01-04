#include "catch.hpp"
#include "../src/BoxChanger_Reg.h"

using namespace std;

TEST_CASE("Adding notes to BoxChanger adds the notes to the contained box.")
{
    std::chrono::time_point<std::chrono::high_resolution_clock> timeStamp = std::chrono::high_resolution_clock::now();
    BoxNote note0{10, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note1{11, Position{1,1}, Position{2,1}, timeStamp};
    BoxNote note2{10, Position{3,1}, Position{1,1}, timeStamp};
    BoxNote note3{11, Position{3,1}, Position{1,1}, timeStamp};
    BoxNote note4{10, Position{4,1}, Position{3,1}, timeStamp};
    BoxNote note5{11, Position{4,1}, Position{3,1}, timeStamp};

    Box box{0, 10, 10};
    BoxChanger_Reg boxChanger{box};
    
    boxChanger.addNote(note0);
    boxChanger.addNote(note1);
    boxChanger.addNote(note2);
    boxChanger.addNote(note3);
    boxChanger.addNote(note4);
    boxChanger.addNote(note5);

    vector<BoxNote> expectedNotes{};
    expectedNotes.push_back(note0);
    expectedNotes.push_back(note1);
    expectedNotes.push_back(note2);
    expectedNotes.push_back(note3);
    expectedNotes.push_back(note4);
    expectedNotes.push_back(note5);

    REQUIRE(expectedNotes == box.getAllNotes());
}

TEST_CASE("adding notes to BoxChanger changes the last arrived position of contained box.") 
{
    Box box{0, 10, 10};
    BoxChanger_Reg boxChanger{box};
    
    // First boxNote with type 11 which is the arrive type.
    BoxNote boxNote0{11, Position{0,0}, Position{0,0}, std::chrono::high_resolution_clock::now()};
    boxChanger.addNote(boxNote0);
   
    // boxNote1 with type 10 is a "to leave" type.
    BoxNote boxNote1{10, Position{1,0}, Position{0,0}, std::chrono::high_resolution_clock::now()};
    boxChanger.addNote(boxNote1);

    BoxNote boxNote2{11, Position{1,0}, Position{0,0}, std::chrono::high_resolution_clock::now()};
    boxChanger.addNote(boxNote2);

    BoxNote boxNote3{10, Position{1,1}, Position{1,0}, std::chrono::high_resolution_clock::now()};
    boxChanger.addNote(boxNote3);
    
    BoxNote boxNote4{11, Position{1,1}, Position{1,0}, std::chrono::high_resolution_clock::now()};
    boxChanger.addNote(boxNote4);

    // Cut off time
    std::chrono::time_point<std::chrono::high_resolution_clock> cutOffTime =
        std::chrono::high_resolution_clock::now();

    BoxNote boxNote5{10, Position{2,1}, Position{1,1}, std::chrono::high_resolution_clock::now()};
    boxChanger.addNote(boxNote5);

    BoxNote boxNote6{4, Position{2,1}, Position{1,1}, std::chrono::high_resolution_clock::now()};
    boxChanger.addNote(boxNote6);

    REQUIRE(Position{1,1} == box.getPos(cutOffTime));
}
