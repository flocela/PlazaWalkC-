#include "catch.hpp"
#include "../src/Mover_Reg.h"
#include "../src/BoardCallback_Accountant.h"

using namespace std;

TEST_CASE("Mover_Reg adds BoardNotes to Board in the correct order.")
{
    // Set up
    // Register a BoardCallback_Accountant with Board for poistions: PositionA and PositionB.
    vector<Box> boxes{Box{0, 0,  10, 10}};

    Position positionA = {5, 5};
    Position positionB = {5, 6};

    BoardCallback_Accountant accountantPosA{};
    BoardCallback_Accountant accountantPosB{};
     
    Board board{10, 10, boxes};
    board.registerCallback(positionA, accountantPosA);
    board.registerCallback(positionB, accountantPosB);

    // Create Mover_Reg. Add a box to positionA and then move that box from positionA to positionB.
    Mover_Reg mover{boxes[0].getId(), &board};
    REQUIRE(true == mover.addBox(positionA));
    REQUIRE(true == mover.moveBox(positionA, positionB));

    // Get BoardNotes from BoardCallback_Accountants corresponding to positions: PositionA and PositionB.
    vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote>> callbackNotesPosA = accountantPosA.getNotes();
    vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote>> callbackNotesPosB = accountantPosB.getNotes();

    // Results:

    // PositionA should get 4 BoardNotes: ImminentArrival, Arrival, ImminentDeparture, Departure.
    // PositionB should get 2 BoardNotes: ImminentArrival, Arrival. 
    REQUIRE(4 == callbackNotesPosA.size());

    REQUIRE(4 == callbackNotesPosA.size());

    REQUIRE(BoardNote{0,SpotType::to_arrive} == callbackNotesPosA[0].second); // At PositionA Imminent Arrival
    REQUIRE(BoardNote{0,SpotType::arrive} == callbackNotesPosA[1].second); // At PositionA Arrival

    REQUIRE(BoardNote{0, SpotType::to_arrive} == callbackNotesPosB[0].second); // At PostionB Imminent Arrival

    REQUIRE(BoardNote{0, SpotType::to_leave} == callbackNotesPosA[2].second); // At PositionA Imminent Departure

    REQUIRE(BoardNote{0, SpotType::arrive} == callbackNotesPosB[1].second); // At PositionB Arrival

    REQUIRE(BoardNote{0, SpotType::left} == callbackNotesPosA[3].second); // At PositionA Departure
    
    // The BoardNotes should be in order.
    REQUIRE(callbackNotesPosA[1].first - callbackNotesPosA[0].first > std::chrono::milliseconds(0) );
    REQUIRE(callbackNotesPosB[0].first - callbackNotesPosA[1].first > std::chrono::milliseconds(0) );
    REQUIRE(callbackNotesPosA[2].first - callbackNotesPosB[0].first > std::chrono::milliseconds(0) );
    REQUIRE(callbackNotesPosB[1].first - callbackNotesPosA[2].first > std::chrono::milliseconds(0) );
    REQUIRE(callbackNotesPosA[3].first - callbackNotesPosB[1].first > std::chrono::milliseconds(0) );
}

TEST_CASE("Mover_Reg removes box from board.")
{
    // Set up Board, Box, and Mover_Reg.
    vector<Box> boxes{Box{0, 0,  10, 10}};
    Board board{10, 10, boxes};
    Mover_Reg mover{boxes[0].getId(), &board};

    // Register a BoardCallback_Accountant to receive changes from Board's PositionA.
    Position positionA = {5, 5};
    BoardCallback_Accountant accountantForPosA{};

    // Add box to positionA
    REQUIRE(true == mover.addBox(positionA));
    REQUIRE(BoardNote{0, SpotType::arrive} ==  board.getNoteAt(positionA));

    // Remove box from positionA
    REQUIRE(true == mover.removeBox(positionA));
    REQUIRE(BoardNote{-1, SpotType::left} ==  board.getNoteAt(positionA));
} 

    
    
    
