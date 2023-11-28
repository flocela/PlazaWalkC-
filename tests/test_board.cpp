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
    
    Position location = board.getLocation(0);
   
    REQUIRE(location == Position(5, 20)); 
}

TEST_CASE("get box location after box moves. Only one box on board.")
{   
    Board board{100, 100};
    board.insert(0, 10, 10, 5, 20);
  
    vector<Position> potentialPositions{Position{6, 20}, Position{4, 20}, Position{6, 21}}; 
     
    board.move(0, potentialPositions);
   
    Position location = board.getLocation(0);
    cout << "[6, 20]: " << location << endl;
    REQUIRE(location == Position(6, 20));
}

TEST_CASE("get box location after box moves. Box can not go to 1st possible position.")
{   
    Board board{100, 100};
    board.insert(0, 10, 10, 5, 20);
    board.insert(1, 10, 10, 6, 20); // box 0 can not move to where box 1 is.
    // box 0 must move to its second position.
  
    vector<Position> potentialPositions{Position{6, 20}, Position{4, 20}, Position{6, 21}}; 
     
    board.move(0, potentialPositions);
   
    Position location = board.getLocation(0);
    REQUIRE(location == Position(4, 20));
}

// both the first and second possible positions are taken
TEST_CASE("get box location after box moves. Box must go to last possible position.")
{   
    Board board{100, 100};
    board.insert(0, 10, 10, 5, 20);
    board.insert(1, 10, 10, 6, 20); // box 0 can not move to where box 1 is.
    board.insert(2, 10, 10, 4, 20); // box 0 can not move to where box 2 is.
  
    vector<Position> potentialPositions{Position{6, 20}, Position{4, 20}, Position{6, 21}}; 
     
    board.move(0, potentialPositions);
   
    Position location = board.getLocation(0);
    REQUIRE(location == Position(6, 21));
}

// all the positions in the potentialPositions vector have been taken by other boxes.
TEST_CASE("get box location after box moves. Box must can not move to any of the given positions.")
{   
    Board board{100, 100};
    board.insert(0, 10, 10, 5, 20);
    board.insert(1, 10, 10, 6, 20); // box 0 can not move to where box 1 is.
    board.insert(2, 10, 10, 4, 20); // box 0 can not move to where box 2 is.
    board.insert(3, 10, 10, 6, 21); // box 0 can not move to where box 3 is.
  
    vector<Position> potentialPositions{Position{6, 20}, Position{4, 20}, Position{6, 21}}; 
     
    board.move(0, potentialPositions);
   
    Position location = board.getLocation(0);
    REQUIRE(location == Position(5, 20)); // this is Box 0's original position
}

