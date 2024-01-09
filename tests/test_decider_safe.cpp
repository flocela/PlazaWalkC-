#include "catch.hpp"
#include "../src/Decider_Safe.h"

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
    box0.addNote(BoxNote{11, positionA, positionA, std::chrono::high_resolution_clock::now()});
    box0.addNote(BoxNote{10, positionA, positionA, std::chrono::high_resolution_clock::now()});
    board.addNote(positionA, boardNoteArrived);

    Decider_Safe decider{};

    vector<Position> possiblePositions = {positionA};

    Position nextPosition = decider.getNextPosition(possiblePositions, board, boxesPerBoxId);

    REQUIRE(Position{-1, -1} == nextPosition);
}
