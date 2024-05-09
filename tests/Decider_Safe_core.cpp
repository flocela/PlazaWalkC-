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

    // Each SECTION represents a Position with a different SpotType (arrive, to_arrive, _to_leave, and left)

    SECTION("Box0 is at positionA with a SpotType::arrive.")
    {

        // Box0 arrives at positionA.
        board.changeSpot(positionA, BoardNote{0, SpotType::to_arrive}, true);
        board.changeSpot(positionA, BoardNote{0, SpotType::arrive}, true);

        SECTION("Box1 is trying to move to positionA. Verify suggetMoveTo(positionA, ...) returns false since positionA has a SpotType that is not SpotType::left")
        {
            REQUIRE_FALSE(decider.suggestMoveTo(positionA, board));
        }

        SECTION("Verify getNext(possiblePositions) returns the first possiblePosition whose SpotType is SpotType::left and returns a time-to-arrival of 0.")
        {
            // The first possiblePosition is positionA, which has a SpotType of SpotType::to_arrive. It is not returned.
            vector<Position> possiblePositions = {positionA, Position{5, 4}, Position{6, 4}};
            pair<Position, int> next = decider.getNext(possiblePositions, board); 

            REQUIRE(Position{5, 4} == next.first);
            REQUIRE(0 == next.second);
        }

        SECTION("In getNext(possiblePositions), the vector possiblePositions has only one Position, PositionA. Verify Decider returns Position{-1, -1} and time-to-arrival of -1.")
        {
            vector<Position> possiblePositions = {positionA};
            pair<Position, int> next = decider.getNext(possiblePositions, board); 
    
            REQUIRE_FALSE(decider.suggestMoveTo(positionA, board));
            REQUIRE(Position{-1, -1} == next.first); 
            REQUIRE(-1 == next.second);
        }
    }

    SECTION("Box1 is deciding to move to postionA, but Box0 is at positionA with a SpotType::to_arrive. The possiblePositions vector has only one position, positionA. Verify Decider returns an invalid Position and time to departure of -1.")
    {

        // Box0 is to_arrive at positionA. 
        board.changeSpot(positionA, BoardNote{0, SpotType::to_arrive}, true);

        vector<Position> possiblePositions = {positionA};

        pair<Position, int> next = decider.getNext(possiblePositions, board);

        REQUIRE_FALSE(decider.suggestMoveTo(positionA, board));
        REQUIRE(Position{-1, -1} == next.first);
        REQUIRE(-1 == next.second);
    }

    SECTION("Box1 is deciding to move to postionA. Box0 is at positionA with a SpotType::to_leave. The possible Positions vector has only one position, positionA. Verify Decider returns an invalid Position and time-to-arrival.")
    {
        // Box0 arrives, but is about to leave.
        board.changeSpot(positionA, BoardNote{0, SpotType::to_arrive}, true);
        board.changeSpot(positionA, BoardNote{0, SpotType::arrive}, true);
        board.changeSpot(positionA, BoardNote{0, SpotType::to_leave}, true);

        vector<Position> possiblePositions = {positionA};

        pair<Position, int> next = decider.getNext(possiblePositions, board);
   
        REQUIRE_FALSE(decider.suggestMoveTo(positionA, board));
        REQUIRE(Position{-1, -1} == next.first);
        REQUIRE(-1 == next.second);
    }


    SECTION("Box1 is deciding to move to postionA. PositionA is unoccupied. Decider returns PositionA and time-to-arrival of 0, meaning that it is okay to move to PositionA.")
    {
        vector<Position> possiblePositions = {positionA, Position{5, 4}, Position{6, 4}};
       
        pair<Position, int> next = decider.getNext(possiblePositions, board);

        REQUIRE(positionA == next.first);
        REQUIRE(0 == next.second);
        REQUIRE(decider.suggestMoveTo(positionA, board));
    }
}
