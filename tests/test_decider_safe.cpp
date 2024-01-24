#include "catch.hpp"
#include "../src/Decider_Safe.h"
#include <iostream>
using namespace std;

TEST_CASE("box1 is deciding to move to positionA, but box0 occupies positionA. Decider does not return positionA.")
{
    Board board{10, 10};
    Box box0{0, 10, 10};
    unordered_map<int, Box*> boxesPerBoxId{};
    boxesPerBoxId.insert({box0.getId(), &box0});

    BoardNote boardNoteToArrive{2, 0};
    BoardNote boardNoteArrived{4, 0};

    Position positionA{0, 0};

    // box0 has arrived at positionA.
    board.addNote(positionA, boardNoteToArrive);
    board.addNote(positionA, boardNoteArrived);

    Decider_Safe decider{};

    vector<Position> possiblePositions = {positionA};

    Position nextPosition = decider.getNextPosition(possiblePositions, board, boxesPerBoxId);

    REQUIRE(Position{-1, -1} == nextPosition);
}

TEST_CASE("box1 is deciding to move to postionA. box0 occupies positionA, but two notes - each signaling box0 will move - have been registered (BoardNote of Type1 and BoxNote of Type 11). Because box0 still hasn't left, the decider does not return positionA.")
{
    Board board{10, 10};
    Box box0{0, 10, 10};
    
    unordered_map<int, Box*> boxesPerBoxId{};
    boxesPerBoxId.insert({box0.getId(), &box0});

    BoardNote boardNoteToLeave{1, 0};
    BoardNote boardNoteToArrive{2, 0};
    BoardNote boardNoteArrived{4, 0};

    Position positionA{0, 0};
    Position positionB{1, 1};

    // box0 has arrived at positionA.
    board.addNote(positionA, boardNoteToArrive);
    board.addNote(positionA, boardNoteArrived);

    // BoardNote signaling box0 will move from positionA is registered with board.
    // BoxNote signaling box0 will move from positionA is registered with box0.
    board.addNote(positionA, boardNoteToLeave);

    Decider_Safe decider{};

    vector<Position> possiblePositions = {positionA};

    Position nextPosition = decider.getNextPosition(possiblePositions, board, boxesPerBoxId);

    REQUIRE(Position{-1, -1} == nextPosition);
}

TEST_CASE("box1 is deciding to move to postionA. box0 originally occupies positionA. A BoxNote is registered with box0 that indicates box0 has left. But a BoardNote indicated box0 has left is not registered to the board. Because the box has actually left the decider returns positionA the next position.")
{
    Board board{10, 10};
    Box box0{0, 10, 10};
    
    unordered_map<int, Box*> boxesPerBoxId{};
    boxesPerBoxId.insert({box0.getId(), &box0});

    BoardNote boardNoteToLeave{1, 0};
    BoardNote boardNoteToArrive{2, 0};
    BoardNote boardNoteLeft{3, 0};
    BoardNote boardNoteArrived{4, 0};

    Position positionA{0, 0};
    Position positionB{1, 1};

    // box0 has arrived at positionA.
    board.addNote(positionA, boardNoteToArrive);
    board.addNote(positionA, boardNoteArrived);

    // BoardNote signaling box0 will move from positionA is registered with board.
    // BoxNote signaling box0 will move from positionA is registered with box0.
    board.addNote(positionA, boardNoteToLeave);

    Decider_Safe decider{};

    vector<Position> possiblePositions = {positionA, Position{2, 2}};

    Position nextPosition = decider.getNextPosition(possiblePositions, board, boxesPerBoxId);

    REQUIRE(positionA == nextPosition);
}

TEST_CASE("box1 is deciding to move to postionA. box0 originally occupies positionA. A BoxNote is registered with box0 that indicates box0 has left. A BoardNote indicating that box0 has left is registered with the board. Because box1 has left, the decider returns positionA as the next position.")
{
    Board board{10, 10};
    Box box0{0, 10, 10};
    
    unordered_map<int, Box*> boxesPerBoxId{};
    boxesPerBoxId.insert({box0.getId(), &box0});

    BoardNote boardNoteToLeave{1, 0};
    BoardNote boardNoteToArrive{2, 0};
    BoardNote boardNoteLeft{3, 0};
    BoardNote boardNoteArrived{4, 0};

    Position positionA{0, 0};
    Position positionB{1, 1};

    // box0 has arrived at positionA.
    board.addNote(positionA, boardNoteToArrive);
    board.addNote(positionA, boardNoteArrived);

    // BoardNote signaling box0 will move from positionA is registered with board.
    // BoxNote signaling box0 will move from positionA is registered with box0.
    board.addNote(positionA, boardNoteToLeave);

    // BoxNote signalling box0 has moved to positionB is registered with box0.

    board.addNote(positionA, boardNoteLeft);

    Decider_Safe decider{};

    vector<Position> possiblePositions = {positionA, Position{2, 2}};

    Position nextPosition = decider.getNextPosition(possiblePositions, board, boxesPerBoxId);

    REQUIRE(positionA == nextPosition);
}
