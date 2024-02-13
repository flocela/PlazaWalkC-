#include "catch.hpp"
#include "../src/Decider_Safe.h"
#include <iostream>
using namespace std;

TEST_CASE("Box0 is deciding to move to positionA, but Box1 occupies positionA. Decider returns the next position.")
{
    Board board{10, 10};
    Position positionA{5, 5};

    // Box1 arrives at positionA. 
    BoardNote boardNoteToArrive{1, 2};
    BoardNote boardNoteArrived{1, 4};
    board.addNote(positionA, boardNoteToArrive);
    board.addNote(positionA, boardNoteArrived);

    Decider_Safe decider{};

    vector<Position> possiblePositions = {positionA, Position{5, 4}, Position{6, 4}};

    Position nextPosition = decider.getNextPosition(possiblePositions, board);

    // Decider does not return positionA because that's where Box1 is. It returns the next position.
    REQUIRE(Position{5, 4} == nextPosition);
}

TEST_CASE("Box0 is deciding to move to positionA, but Box1 occupies positionA. The decider is given a vector with only one position, PositionA. Because there are no other positions to choose, Decider returns Position{-1, -1}.")
{
    Board board{10, 10};
    Position positionA{5, 5};

    // Box1 arrives at positionA. 
    BoardNote boardNoteToArrive{1, 2};
    BoardNote boardNoteArrived{1, 4};
    board.addNote(positionA, boardNoteToArrive);
    board.addNote(positionA, boardNoteArrived);

    Decider_Safe decider{};

    vector<Position> possiblePositions = {positionA};

    // Decider does not return positionA because that's where Box1 is. It returns {-1, -1} because the possiblePositions vector only had one position.
    Position nextPosition = decider.getNextPosition(possiblePositions, board);
    REQUIRE(Position{-1, -1} == nextPosition);
}

TEST_CASE("Box0 is deciding to move to postionA. Box1 has sent a note to Board that it will arrive at positionA. Because positionA will be occupied, Decider returns Position{-1, -1} deciding not to move to PositionA")
{
    Board board{10, 10};
    Position positionA{5, 5};

    // BoardNote{boxId, type}. Box1 signals that it will arrive.
    BoardNote boardNoteToArrive{1, 2};
    board.addNote(positionA, boardNoteToArrive);

    Decider_Safe decider{};

    vector<Position> possiblePositions = {positionA};

    Position nextPosition = decider.getNextPosition(possiblePositions, board);

    REQUIRE(Position{-1, -1} == nextPosition);
}

TEST_CASE("Box0 is deciding to move to postionA. Box1 occupies positionA, but has given a type 1 (imminent departure) note to the board. The decider still returns Position{-1, -1} because the position is occupied.")
{
    Board board{10, 10};
    Position positionA{5, 5};

    // BoardNote{boxId, type}. Box1 arrives, but is about to leave.
    BoardNote boardNoteToArrive{1, 2};
    BoardNote boardNoteArrived{1, 4};
    BoardNote boardNoteAboutToLeave{1, 1};
    board.addNote(positionA, boardNoteToArrive);
    board.addNote(positionA, boardNoteArrived);
    board.addNote(positionA, boardNoteAboutToLeave);

    Decider_Safe decider{};

    vector<Position> possiblePositions = {positionA};

    Position nextPosition = decider.getNextPosition(possiblePositions, board);

    REQUIRE(Position{-1, -1} == nextPosition);
}


TEST_CASE("Box0 is deciding to move to postionA. PositionA is unoccupied. Decider returns PositionA meaning that it is okay to move to PositionA.")
{
    Board board{10, 10};
    Position positionA{5, 5};

    Decider_Safe decider{};

    vector<Position> possiblePositions = {positionA, Position{5, 4}, Position{6, 4}};
   
    Position nextPosition = decider.getNextPosition(possiblePositions, board);

    REQUIRE(positionA == nextPosition);
}
