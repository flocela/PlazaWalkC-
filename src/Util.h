#ifndef UTIL__H
#define UTIL__H

#include <random>
#include <vector>
#include "Box.h"
#include "Position.h"

class Util
{
public:

    // Returns a random int in the range [start, end].
    static int getRandomInt(int start, int end);
   
    // Returns count number of random ints in the range [start, end]. 
    static std::vector<int>  getRandomInt(int start, int end, int count);

    static bool getRandomBool();

    // Returns count number of random Positions in the rectangle made by @a and @b. Positions on the edge of the rectangle are valid and could be returned. If @a is {ax, ay} and @b is {bx, by}, then a Position {ax, by} could be returned.
    static std::vector<Position> getRandomPositionsInRectangle(Position a, Position b, int count);

    // Returns a random Position in the rectangle made by Positions cornerA and cornerB. Positions on the edge of the rectangle are valid and could be returned. If @a is {ax, ay} and @b is {bx, by}, then a Position {ax, by} could be returned.
    static Position getRandomPositionInRectangle(Position cornerA, Position cornerB);

    // Suffles a vector of any type.
    template<typename T>
    static void utilShuffle(std::vector<T>& v)
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(v.begin(), v.end(), g);
    }
};

#endif
    
