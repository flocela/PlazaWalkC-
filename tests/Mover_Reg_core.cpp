#include "catch.hpp"
#include "../src/Mover_Reg.h"
#include "../src/NoteAccountant.h"

using namespace std;

TEST_CASE("Mover_Reg_core::")
{
    SECTION("In addBox() and moveBox(), Mover_Reg adds BoardNotes to Board in the correct order.")
    {
        // Register a NoteAccountant with Board for positions: startPosition and endPosition.
        Position startPosition = {5, 5};
        NoteAccountant startPositionAccountant{};
        Position endPosition = {5, 6};
        NoteAccountant endPositionAccountant{};
         
        vector<Box> boxes{Box{0, 0,  10, 10}};
        Board board{10, 10, std::move(boxes)};
        board.registerNoteSubscriber(startPosition, startPositionAccountant);
        board.registerNoteSubscriber(endPosition, endPositionAccountant);

        // Create Mover_Reg. Add a box to startPosition. Then move that box from startPosition to endPosition.
        Mover_Reg mover{boxes[0].getId(), &board};
        REQUIRE(true == mover.addBox(startPosition));
        REQUIRE(true == mover.moveBox(startPosition, endPosition));

        // Get BoardNotes from accountants per position.
        vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote>> startPosNotes = startPositionAccountant.getNotes();
        vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote>> endPosNotes = endPositionAccountant.getNotes();

        // Results:

        // startPosition should get 4 BoardNotes: SpotType::to_arrive, SpotType::arrive, SpotType::to_leave, SpotType::left.

        // endPosition should get 2 BoardNotes: SpotType::to_arrive and SpotType::arrive. 
        REQUIRE(4 == startPosNotes.size());

        REQUIRE(2 == endPosNotes.size());

        // From startPosNotes: Box 0 is to_arrive.
        REQUIRE(BoardNote{0,SpotType::to_arrive} == startPosNotes[0].second); 

        // From startPosNotes: Box 0 has arrived.
        REQUIRE(BoardNote{0,SpotType::arrive} == startPosNotes[1].second); 

        // From endPosNotes: Box 0 is to_arrive.
        REQUIRE(BoardNote{0, SpotType::to_arrive} == endPosNotes[0].second); 

        // From startPosNotes: Box 0 is to_leave.
        REQUIRE(BoardNote{0, SpotType::to_leave} == startPosNotes[2].second); 

        // From endPosNotes: Box 0 is arrive.
        REQUIRE(BoardNote{0, SpotType::arrive} == endPosNotes[1].second); 

        // From startPosNotes: Box 0 has left.
        REQUIRE(BoardNote{0, SpotType::left} == startPosNotes[3].second); 
        
        // The BoardNotes should be in order.
        
        // startPosNotes[0] is Box0 is to_arrive, statePosNotes[1] is Box0 arrive.
        REQUIRE(startPosNotes[1].first - startPosNotes[0].first > std::chrono::milliseconds(0) );

        // startPosNotes[1] is Box0 arrive. endPosNotes[0] is Box0 to_arrive.
        REQUIRE(endPosNotes[0].first - startPosNotes[1].first > std::chrono::milliseconds(0) );

        // endPosNotes[0] is Box0 to_arrive. startPosNotes[2] is Box0 to_leave.
        REQUIRE(startPosNotes[2].first - endPosNotes[0].first > std::chrono::milliseconds(0) );

        // startPosNotes[2] is Box0 to_leave. endPosNotes[1] is Box0 arrive.
        REQUIRE(endPosNotes[1].first - startPosNotes[2].first > std::chrono::milliseconds(0) );

        // endPosNotes[1] is Box0 arrive. startPosNotes[3] is Box0 left.
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

    SECTION("Adding Box to a Position that already has a Box returns false.")
    {
        Position position = {5, 5};
       
        // Two boxes. 
        vector<Box> boxes{Box{0, 0,  10, 10}, Box{1, 0, 10, 10}};
        Board board{10, 10, std::move(boxes)};
        Mover_Reg mover0{boxes[0].getId(), &board};
        Mover_Reg mover1{boxes[1].getId(), &board};
        
        mover0.addBox(position);
        REQUIRE_FALSE(mover1.addBox(position));
    }
         
    SECTION("Moving Box to a Position that already has a Box returns false.")
    {
        Position positionA = {5, 5};
        Position positionB = {6, 6};
       
        // Two boxes. 
        vector<Box> boxes{Box{0, 0,  10, 10}, Box{1, 0, 10, 10}};
        Board board{10, 10, std::move(boxes)};
        Mover_Reg mover0{boxes[0].getId(), &board};
        Mover_Reg mover1{boxes[1].getId(), &board};
        
        mover0.addBox(positionA);
        mover1.addBox(positionB);

        REQUIRE_FALSE(mover0.moveBox(positionA, positionB));
    }
}
    
