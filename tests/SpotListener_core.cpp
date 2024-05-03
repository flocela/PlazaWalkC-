#include "catch.hpp"
#include "../src/SpotListener.h"

using namespace std;

TEST_CASE("SpotListener_core::")
{
    SECTION("Verify that SpotListeners save all BoardNotes they receive.")
    {
        SpotListener spotListener{};
        spotListener.receiveCombinedString("B10, T1");
        spotListener.receiveCombinedString("B10, T2");

        vector<string> successfulNotes =spotListener.getCombinedStrings();
        REQUIRE("B10, T1" == successfulNotes[0]);
        REQUIRE("B10, T2" == successfulNotes[1]);
    }
}
