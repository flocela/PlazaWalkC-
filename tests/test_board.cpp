#include "catch.hpp"
#include "../src/Board.h"

#include <memory>

using namespace std;

TEST_CASE("set and get dimensions")
{
    Board board{10, 20};
    REQUIRE(board.getHeight() == 10);
    REQUIRE(board.getWidth() == 20); 
    
    board.setHeight(5);    
    board.setWidth(15);

    REQUIRE(board.getHeight() == 5);
    REQUIRE(board.getWidth() == 15); 
}

TEST_CASE("get location of box. Easy - one box exists and doesn't move")
{
    
    Board board{100, 100};
    board.insert(0, 10, 10, 5, 20);
    
    pair<int, int> location = board.getLocation(0);
    
    REQUIRE(location.first == 5);
    REQUIRE(location.second == 20);
}

TEST_CASE("get location when box moves. Only one box on board.")
{
    Board board{100, 100};
    board.insert(0, 10, 10, 5, 20);
  
    vector<Position> positionsToMoveTo{Position{6, 20}, Position{4, 20}, Position{6, 21}}; 
     
    board.move(0, positionsToMoveTo);
   
    pair<int, int> location = board.getLocation(0);
    REQUIRE(location.first == 6);
    REQUIRE(location.second == 20);
}
