#include "catch.hpp"
#include "../src/BoardCallback_Printer.h"
#include <iostream>

using namespace std;

class TestPrinter : public Printer
{
public:

    void print(const Board& board, Position position) override
    {
       _receivedBoardNotes.push_back({std::chrono::high_resolution_clock::now(), {board.getNoteAt(position), position}}); 
    }

    vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, pair<BoardNote, Position>>> _receivedBoardNotes;

};

TEST_CASE("BoardCallback_Printer:: Adding a BoardNote to the board, should result in a callback message sent to the callBack object.")
{
    Position pos0{0, 0};
    Board board{10, 10};
    TestPrinter testPrinter{};
    BoardCallback_Printer callbackObject{&board, &testPrinter};
    board.registerCallback(&callbackObject);

    BoardNote noteBox0Type2{0, 2}; // box 0 is about to arrive
    BoardNote noteBox0Type4{0, 4}; // box 0 arrives
    
    board.addNote(pos0, noteBox0Type2);
    board.addNote(pos0, noteBox0Type4);

    REQUIRE(2 == testPrinter._receivedBoardNotes.size());
    REQUIRE(noteBox0Type2 == testPrinter._receivedBoardNotes[0].second.first);
    REQUIRE(pos0 == testPrinter._receivedBoardNotes[0].second.second);
    REQUIRE(noteBox0Type4 == testPrinter._receivedBoardNotes[1].second.first);
    REQUIRE(pos0 == testPrinter._receivedBoardNotes[1].second.second);
}
