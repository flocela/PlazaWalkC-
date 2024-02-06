#include "catch.hpp"
#include "../src/Mover_Reg.h"
#include "../src/BoardCallback_Accountant.h"

using namespace std;

TEST_CASE("Mover_Reg adds BoardNotes to Board in the correct order.")
{
    Box box{1, 10, 10};

    Position posA = {5, 5};
    Position posB = {5, 6};

    BoardCallback_Accountant accountantPosA{};
    BoardCallback_Accountant accountantPosB{};
     
    Board board{10, 10};
    board.registerCallback(posA, accountantPosA);
    board.registerCallback(posB, accountantPosB);

    Mover_Reg mover{box, board};
    REQUIRE(true == mover.addBox(posA));
    REQUIRE(true == mover.moveBox(posA, posB));

    vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote>> callbackNotesPosA = accountantPosA.getNotes();
    vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote>> callbackNotesPosB = accountantPosB.getNotes();

    // PositionA should get 4 BoardNotes: ImminentArrival, Arrival, ImminentDeparture, Departure.
    // PositionB should get 2 BoardNotes: ImminentArrival, Arrival. 

    REQUIRE(4 == callbackNotesPosA.size());

    REQUIRE(4 == callbackNotesPosA.size());

    REQUIRE(BoardNote{1,2} == callbackNotesPosA[0].second); // At PositionA Imminent Arrival
    REQUIRE(BoardNote{1,4} == callbackNotesPosA[1].second); // At PositionA Arrival

    REQUIRE(BoardNote{1,2} == callbackNotesPosB[0].second); // At PostionB Imminent Arrival

    REQUIRE(BoardNote{1,1} == callbackNotesPosA[2].second); // At PositionA Imminent Departure

    REQUIRE(BoardNote{1,4} == callbackNotesPosB[1].second); // At PositionB Arrival

    REQUIRE(BoardNote{1,3} == callbackNotesPosA[3].second); // At PositionA Departure
    

    REQUIRE(callbackNotesPosA[1].first - callbackNotesPosA[0].first > std::chrono::milliseconds(0) );
    REQUIRE(callbackNotesPosB[0].first - callbackNotesPosA[1].first > std::chrono::milliseconds(0) );
    REQUIRE(callbackNotesPosA[2].first - callbackNotesPosB[0].first > std::chrono::milliseconds(0) );
    REQUIRE(callbackNotesPosB[1].first - callbackNotesPosA[2].first > std::chrono::milliseconds(0) );
    REQUIRE(callbackNotesPosA[3].first - callbackNotesPosB[1].first > std::chrono::milliseconds(0) );
}
