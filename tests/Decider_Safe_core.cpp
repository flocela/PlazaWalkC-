#include "catch.hpp"
#include "../src/Decider_Safe.h"

using namespace std;

TEST_CASE("Decider_Safe_core::")
{
    // Board and positionA
    Board board{10, 10, vector<Box>{Box{0, 0, 1, 1}}};
    Position positionA{5, 5};

    // Decider_Safe
    Decider_Safe decider{};

    SECTION("Box1 is deciding to move to positionA, but Box0 is at positionA with a SpotType::arrive.")
    {

        // Box0 arrives at positionA.
        board.addNote(positionA, BoardNote{0, SpotType::to_arrive});
        board.addNote(positionA, BoardNote{0, SpotType::arrive});
       
        SECTION("Decider returns the next position and time-to-departure of zero.")
        {
            vector<Position> possiblePositions = {positionA, Position{5, 4}, Position{6, 4}};
            pair<Position, int> next = decider.getNext(possiblePositions, board); 

            REQUIRE(Position{5, 4} == next.first);
            REQUIRE(0 == next.second);
        }

        SECTION("The vector possiblePositions has only one Position, PositionA. Because there are no other positions to choose, Decider returns Position{-1, -1} and time-to-departure of -1.")
        {
            vector<Position> possiblePositions = {positionA};
            pair<Position, int> next = decider.getNext(possiblePositions, board); 

            REQUIRE(Position{-1, -1} == next.first); 
            REQUIRE(-1 == next.second);
        }
    }

    SECTION("Box1 is deciding to move to postionA, but Box0 is at positionA with a SpotType::to_arrive. The possiblePositions vector has only one position, positionA, so Decider returns an invalid Position and time to departure.")
    {

        // Box0 is to_arrive at positionA. 
        BoardNote boardNoteToArrive{0, SpotType::to_arrive};
        board.addNote(positionA, BoardNote{0, SpotType::to_arrive});

        vector<Position> possiblePositions = {positionA};

        pair<Position, int> next = decider.getNext(possiblePositions, board);

        REQUIRE(Position{-1, -1} == next.first);
        REQUIRE(-1 == next.second);
    }

    SECTION("Box1 is deciding to move to postionA. Box0 is at positionA with a SpotType::to_leave. The possible Positions vector has only one position, positionA, so Decider returns an invalid Position and time to departure.")
    {
        // Box0 arrives, but is about to leave.
        board.addNote(positionA, BoardNote{0, SpotType::to_arrive});
        board.addNote(positionA, BoardNote{0, SpotType::arrive});
        board.addNote(positionA, BoardNote{0, SpotType::to_leave});

        vector<Position> possiblePositions = {positionA};

        pair<Position, int> next = decider.getNext(possiblePositions, board);

        REQUIRE(Position{-1, -1} == next.first);
        REQUIRE(-1 == next.second);
    }


    SECTION("Box1 is deciding to move to postionA. PositionA is unoccupied. Decider returns PositionA meaning that it is okay to move to PositionA.")
    {
        vector<Position> possiblePositions = {positionA, Position{5, 4}, Position{6, 4}};
       
        pair<Position, int> next = decider.getNext(possiblePositions, board);

        REQUIRE(positionA == next.first);
        REQUIRE(0 == next.second);
    }
}
