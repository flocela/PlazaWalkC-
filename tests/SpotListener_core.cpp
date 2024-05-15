#include "catch.hpp"
#include "../src/SpotListener.h"

using namespace std;

TEST_CASE("SpotListener_core::")
{
    SECTION("Verify that SpotListeners save all BoardNotes they receive.")
    {
        SpotListener spotListener{};
        spotListener.receiveStateString("B10, MoveType::left");
        spotListener.receiveStateString("B10, MoveType::to_arrive");

        vector<string> successfulNotes =spotListener.getStateStrings();
        REQUIRE("B10, MoveType::left" == successfulNotes[0]);
        REQUIRE("B10, MoveType::to_arrive" == successfulNotes[1]);
    }
}
