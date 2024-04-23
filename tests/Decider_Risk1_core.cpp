#include "catch.hpp"
#include "../src/Decider_Risk1.h"

using namespace std;

TEST_CASE("Decider_Risk1_core::")
{

    // Vector of Boxes 
    vector<Box> boxes{
        Box{0, 0, 10, 10}, // boxId = 0
        Box{1, 1, 10, 10}, // boxId = 1
        Box{2, 2, 10, 10}}; // boxId = 1

    // Positions with different SpotTypes.
    Position positionTypeToArrive{0, 0};
    Position positionTypeArrive{1, 1};
    Position positionTypeToLeave{2, 2};
    Position positionTypeLeft{3, 3};

    // Board
    Board board{10, 10, std::move(boxes)};

    // Box at index 0, at Position{0, 0} has a SpotType of SpotType::to_arrive. 
    board.addNote(positionTypeToArrive, BoardNote{0, SpotType::to_arrive});

    // Box at index 1, at Position{1, 1} has a SpotType of SpotType::arrive.
    board.addNote(positionTypeArrive, BoardNote{1, SpotType::to_arrive});
    board.addNote(positionTypeArrive, BoardNote{1, SpotType::arrive});
    
    // Box at index 2, at Position{2, 2} has a SpotType of SpotType::to_leave.
    board.addNote(positionTypeToLeave, BoardNote{2, SpotType::to_arrive});
    board.addNote(positionTypeToLeave, BoardNote{2, SpotType::arrive});
    board.addNote(positionTypeToLeave, BoardNote{2, SpotType::to_leave});
    

    // Decider_Risk1
    Decider_Risk1 decider{};
    SECTION("Box3 is deciding to move to positionTypeToArrive which has a SpotType::to_arrive.")
    {
        SECTION("suggestMoveTo() returns false")
        {
            REQUIRE_FALSE(decider.suggestMoveTo(positionTypeToArrive, board));
        }
        SECTION("getNext() returns the first possiblePositions that is SpotType::to_leave or SpotType::left")
        {
            vector<Position> possiblePositions = {positionTypeToArrive, positionTypeLeft, positionTypeToLeave};
            pair<Position, int> next = decider.getNext(possiblePositions, board);
            REQUIRE(positionTypeLeft == next.first);
            REQUIRE(0 == next.second);

            possiblePositions = {positionTypeToArrive, positionTypeToLeave, positionTypeLeft};
            next = decider.getNext(possiblePositions, board);
            REQUIRE(positionTypeToLeave == next.first);
            REQUIRE(7 == next.second);
        }
    }
    SECTION("Box3 is deciding to move to positionTypeArrive which has a SpotType::arrive.")
    {
        SECTION("suggestMoveTo() returns false")
        {
            REQUIRE_FALSE(decider.suggestMoveTo(positionTypeArrive, board));
        }
        SECTION("getNext() returns the first possiblePositions that is SpotType::to_leave or SpotType::left")
        {
            vector<Position> possiblePositions = {positionTypeArrive, positionTypeLeft, positionTypeToLeave};
            pair<Position, int> next = decider.getNext(possiblePositions, board);
            REQUIRE(positionTypeLeft == next.first);
            REQUIRE(0 == next.second);
        }
    }
    SECTION("Box3 is deciding to move to positionTypeToLeave which has a SpotType::toLeave.")
    {
        SECTION("suggestMoveTo() returns true")
        {
            REQUIRE(decider.suggestMoveTo(positionTypeToLeave, board));
        }
        SECTION("possiblePositions starts with positionTypeToLeave. It is the first possiblePosition that is SpotType::to_leave or SpotType::left, so it will be returned.")
        {
            vector<Position> possiblePositions = {positionTypeToLeave, positionTypeLeft, positionTypeToLeave};
            pair<Position, int> next = decider.getNext(possiblePositions, board);
            REQUIRE(positionTypeToLeave == next.first);
            REQUIRE(7 == next.second);
        }
    }
    SECTION("Box3 is deciding to move to positionTypeLeft which has a SpotType::Left.")
    {
        SECTION("suggestMoveTo() returns true")
        {
            REQUIRE(decider.suggestMoveTo(positionTypeLeft, board));
        }
        SECTION("possiblePositions starts with positionTypeLeft. It is the first possiblePosition that is SpoteType::to_leave or SpotType::left, so it will be returnd.")
        {
            vector<Position> possiblePositions = {positionTypeLeft, positionTypeLeft, positionTypeToLeave};
            pair<Position, int> next = decider.getNext(possiblePositions, board);
            REQUIRE(positionTypeLeft == next.first);
            REQUIRE(0 == next.second);
        }
    }
}
