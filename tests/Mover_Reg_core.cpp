#include "catch.hpp"
#include "../src/Mover_Reg.h"
#include "../src/NoteAccountant.h"

using namespace std;

TEST_CASE("Mover_Reg_core::")
{
    SECTION("In addBox() and moveBox(), Mover_Reg adds BoardNotes to Board in the correct order.")
    {
        // Set up
        // Register a NoteAccountant with Board for poistions: startPosition and endPosition.
        vector<Box> boxes{Box{0, 0,  10, 10}};

        Position startPosition = {5, 5};
        Position endPosition = {5, 6};

        NoteAccountant startAccountant{};
        NoteAccountant endAccountant{};
         
        Board board{10, 10, std::move(boxes)};
        board.registerNoteSubscriber(startPosition, startAccountant);
        board.registerNoteSubscriber(endPosition, endAccountant);

        // Create Mover_Reg. Add a box to startPosition. Then move that box from startPosition to endPosition.
        Mover_Reg mover{boxes[0].getId(), &board};
        REQUIRE(true == mover.addBox(startPosition));
        REQUIRE(true == mover.moveBox(startPosition, endPosition));

        // Get BoardNotes from accountants per position.
        vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote>> startPosNotes = startAccountant.getNotes();
        vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote>> endPosNotes = endAccountant.getNotes();

        // Results:

        // startPosition should get 4 BoardNotes: ImminentArrival, Arrival, ImminentDeparture, Departure.
        // endPosition should get 2 BoardNotes: ImminentArrival, Arrival. 
        REQUIRE(4 == startPosNotes.size());

        REQUIRE(4 == startPosNotes.size());

        // From startPosNotes: Box 0 is to_arrive.
        REQUIRE(BoardNote{0,SpotType::to_arrive} == startPosNotes[0].second); 

        // From startPosNotes: Box 0 has arrived.
        REQUIRE(BoardNote{0,SpotType::arrive} == startPosNotes[1].second); 

        // From endPosNotes: Box 0 is to_arrive.
        REQUIRE(BoardNote{0, SpotType::to_arrive} == endPosNotes[0].second); 

        // From startPosNotes: Box 0 is to_leave.
        REQUIRE(BoardNote{0, SpotType::to_leave} == startPosNotes[2].second); 

        // From endPosNotes: Box 0 is to_arrive.
        REQUIRE(BoardNote{0, SpotType::arrive} == endPosNotes[1].second); 

        // From startPosNotes: Box 0 has left.
        REQUIRE(BoardNote{0, SpotType::left} == startPosNotes[3].second); 
        
        // The BoardNotes should be in order.
        REQUIRE(startPosNotes[1].first - startPosNotes[0].first > std::chrono::milliseconds(0) );
        REQUIRE(endPosNotes[0].first - startPosNotes[1].first > std::chrono::milliseconds(0) );
        REQUIRE(startPosNotes[2].first - endPosNotes[0].first > std::chrono::milliseconds(0) );
        REQUIRE(endPosNotes[1].first - startPosNotes[2].first > std::chrono::milliseconds(0) );
        REQUIRE(startPosNotes[3].first - endPosNotes[1].first > std::chrono::milliseconds(0) );
    }
    
    SECTION("Mover_Reg removes box from board.")
    {
        // Set up Board, Box, and Mover_Reg.
        vector<Box> boxes{Box{0, 0,  10, 10}};
        Board board{10, 10, std::move(boxes)};
        Mover_Reg mover{boxes[0].getId(), &board};

        // Register a NoteAccountant to receive changes from Board's positionsFrom.
        Position startPosition = {5, 5};
        NoteAccountant accountantForPosA{};

        // Add box to startPosition
        REQUIRE(true == mover.addBox(startPosition));
        REQUIRE(BoardNote{0, SpotType::arrive} ==  board.getNoteAt(startPosition));

        // Remove box from startPosition
        REQUIRE(true == mover.removeBox(startPosition));
        REQUIRE(BoardNote{-1, SpotType::left} ==  board.getNoteAt(startPosition));
    } 
}


    
    
    
