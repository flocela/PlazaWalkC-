#ifndef UTIL__H
#define UTIL__H

#include <random>
#include <vector>
#include "Position.h"
#include "Rectangle.h"

class Util
{
public:

    /*
    Returns a random int in the range [@start, @end].
    */
    static int getRandomInt(int start, int end);
   
    /*
    Returns @count number of random ints in the range [@start, @end].
    */
    static std::vector<int>  getRandomInt(int start, int end, int count);

    /*
    Randomly returns true or false.
    */
    static bool getRandomBool();

    /*
    Returns @count number of random Positions from inside the Rectangle @rectangle. Positions on the edge of the Rectangle are valid and could be returned. If the top left corner is Position{ax, ay} and the bottom right corner is Position{bx, by}, then a Position {ax, by} could be returned.
    */
    static std::vector<Position> getRandomPositionsInRectangle(Rectangle rectangle, int count);

    /*
    Returns a random Position from the inside of the Rectangle @rectangle. If the top left corner is Position{ax, ay} and the bottom right corner is Position{bx, by}, then a Position {ax, by} could be returned.
    */
    static Position getRandomPositionInRectangle(Rectangle rectangle);

};

#endif
    
