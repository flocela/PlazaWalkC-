#include "Util.h"

using namespace std;

int  Util::getRandomInt(int start, int end)
{
    int min = std::min(start, end);
    int max = std::max(start, end);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(min, max);
   
    return distribution(gen);

}
vector<int> Util::getRandomInt(int start, int end, int count)
{
    int min = std::min(start, end);
    int max = std::max(start, end);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(min, max);
   
    vector<int> randomInts{};
    for(int ii=0; ii<count; ++ii)
    {
        randomInts.push_back(distribution(gen));
    }
    return randomInts;
}

bool Util::getRandomBool()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(0, 1);
    return static_cast<bool>(distribution(gen));
}

vector<Position> Util::getRandomPositionsInRectangle(Position cornerA, Position cornerB, int count)
{
    int x1 = cornerA.getX();
    int x2 = cornerB.getX();
    int y1 = cornerA.getY();
    int y2 = cornerB.getY();

    vector<int> randomXs = getRandomInt(x1, x2, count);
    vector<int> randomYs = getRandomInt(y1, y2, count);

    vector<Position> positions{};
    for(int ii=0; ii<count; ++ii)
    {
        positions.push_back({randomXs[ii], randomYs[ii]});
    }
    
    return positions;
}

Position Util::getRandomPositionInRectangle(Position cornerA, Position cornerB)
{
    int x1 = cornerA.getX();
    int x2 = cornerB.getX();
    int y1 = cornerA.getY();
    int y2 = cornerB.getY();

    return Position{getRandomInt(x1, x2), getRandomInt(y1, y2)};
}

    
