#ifndef UTIL__H
#define UTIL__H

#include <random>
#include <vector>
#include "Position.h"

class Util
{
public:

    static std::vector<int>  getRandom(int start, int end, int count);

    static std::vector<Position> getRandomInRectangle(Position a, Position b, int count);
};

#endif
    
