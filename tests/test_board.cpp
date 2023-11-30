#include "catch.hpp"
#include "../src/Board.h"

#include <memory>

using namespace std;

TEST_CASE("setHeight(int height) and setWidth(int width) set the Board's dimensions. getHeight() and getWidth() return the Board's dimensions")
{
    Board board{10, 20};
    REQUIRE(board.getHeight() == 10);
    REQUIRE(board.getWidth() == 20); 
    
    board.setHeight(5);    
    board.setWidth(15);

    REQUIRE(board.getHeight() == 5);
    REQUIRE(board.getWidth() == 15); 
}

TEST_CASE("getLocation(int boxId) returns the location of the given box id.")
{
    
    Board board{100, 100};
    board.insert(0, 10, 10, 5, 20);
    
    Position location = board.getLocation(0);
   
    REQUIRE(location == Position(5, 20)); 
}

TEST_CASE("If move(int boxId, vector<Positions> positions) is called and the first position is open, then the box moves to the first position in positions vector")
{
    Board board{100, 100};
    board.insert(0, 10, 10, 5, 20);
  
    vector<Position> potentialPositions{Position{6, 20}, Position{4, 20}, Position{6, 21}}; 
     
    board.move(0, potentialPositions);
   
    Position location = board.getLocation(0);
    cout << "[6, 20]: " << location << endl;
    REQUIRE(location == Position(6, 20));
}

TEST_CASE("If move(int boxId, vector<Positions> positions) is called and the first position is taken, then the box moves to the second position in positions vector.")
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
TEST_CASE("If move(int boxId, vector<Positions> positions) is called and the first two positions are taken, then the box moves to the last position in positions vector.")
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
TEST_CASE("If move(int boxId, vector<Positions> positions) is called and all the positions are taken, then the box does not move.")
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

TEST_CASE("getCopyOfBoxes() returns the boxes in the Board")
{
}
