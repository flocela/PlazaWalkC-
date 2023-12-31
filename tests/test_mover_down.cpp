#include "catch.hpp"
#include "../src/Mover_Down.h"

using namespace std;

// box is moving down. If Current position is Position(a, b), then 
//      first position is Position(a, b+1). Corresponding to moving down.
//      second position is Position(a+1, b+1).
//      third position is Position(a-1, b+1).
TEST_CASE("Should return next positions, which are down, then the diagonal position down and left, then the diagonal position down and right.")
{
    // note0's type is 4, which means it arrives at Position(5, 5);
    BoxNote note0{4, Position{5, 5}, Position{5, 4}, std::chrono::high_resolution_clock::now()};
    Box box{0, 10, 10};
    box.addNote(note0);

    Mover_Down downMover{};
    vector<Position> positions = downMover.getFuturePositions(box);
    REQUIRE(positions[0] == Position{5, 6});
    REQUIRE(positions[1] == Position{6, 6});
    REQUIRE(positions[2] == Position{4, 6});

}

