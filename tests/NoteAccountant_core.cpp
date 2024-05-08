#include "catch.hpp"
#include "../src/NoteAccountant.h"

using namespace std;

TEST_CASE("NoteAccountant_core.cpp")
{

    SECTION("Saves the received BoardNotes from the callback() method.")
    {
        Position pos0{0, 0};
        NoteAccountant noteAccountant{};

        BoardNote noteToArrive{0, SpotType::to_arrive}; // box 0 is about to arrive
        BoardNote noteArrive{0, SpotType::arrive}; // box 0 arrives

        noteAccountant.callback(noteToArrive); 
        noteAccountant.callback(noteArrive);

        vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote>> callbackNotes = noteAccountant.getNotes();

        REQUIRE(2 == callbackNotes.size());
        REQUIRE(noteToArrive == callbackNotes[0].second);
        REQUIRE(noteArrive == callbackNotes[1].second);
    }
}
