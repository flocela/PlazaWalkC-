#ifndef UTIL__H
#define UTIL__H

#include <random>
#include <vector>
#include "Box.h"
#include "Position.h"

class Util
{
public:

    static int getRandom(int start, int end);

    static std::vector<int>  getRandom(int start, int end, int count);

    static std::vector<Position> getRandomInRectangle(Position a, Position b, int count);

    template<typename T>
    static void utilShuffle(std::vector<T>& v)
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(v.begin(), v.end(), g);
    }
};

#endif
    
