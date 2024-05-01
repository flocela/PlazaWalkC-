#include "catch.hpp"
#include "../src/Mover_Reg.h"
#include "../src/NoteAccountant.h"

using namespace std;

TEST_CASE("Mover_Reg_getters_setters::")
{
    SECTION("getBoxId() returns boxId")
    {
    vector<Box> boxes{Box{10, 0,  12, 12}};
    Board board{10, 10, std::move(boxes)};
    Mover_Reg mover{boxes[0].getId(), &board};
    REQUIRE(10 == mover.getBoxId());
    }
}

    
    
    
