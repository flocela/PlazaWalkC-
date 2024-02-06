#include "catch.hpp"
#include "../src/BoardCallback_Accountant.h"
#include "../src/Board.h"
#include <iostream>

using namespace std;

TEST_CASE("BoardCallback_Accountant:: Adding a BoardNote to the board, should result in a callback message sent to the callBack object.")
{
    Position pos0{0, 0};
    Board board{10, 10};
    BoardCallback_Accountant callbackObject{};
    board.registerCallback(pos0, callbackObject);

    BoardNote noteBox0Type2{0, 2}; // box 0 is about to arrive
    BoardNote noteBox0Type4{0, 4}; // box 0 arrives
    
    board.addNote(pos0, noteBox0Type2);
    board.addNote(pos0, noteBox0Type4);

    vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote>> callbackNotes = callbackObject.getNotes();

    REQUIRE(2 == callbackNotes.size());
    REQUIRE(noteBox0Type2 == callbackNotes[0].second);
    REQUIRE(noteBox0Type4 == callbackNotes[1].second);
}
