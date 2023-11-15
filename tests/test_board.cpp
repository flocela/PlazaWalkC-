#include "catch.hpp"
#include "../src/Board.h"


using namespace std;

TEST_CASE("set and get dimensions")
{
    vector<Box*> boxes{};
    Board board{10, 20, boxes};
    REQUIRE(board.getHeight() == 10);
    REQUIRE(board.getWidth() == 20); 
    
    board.setHeight(5);    
    board.setWidth(15);

    REQUIRE(board.getHeight() == 5);
    REQUIRE(board.getWidth() == 15); 
}


