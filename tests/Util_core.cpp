#include "catch.hpp"
#include "../src/Util.h"

using namespace std;

TEST_CASE("Util_core::")
{
    SECTION("Returns numbers in the range [0, 10].")
    {
        
        unordered_map<int, int> countsPerInts{};
        for(int ii=0; ii<10000; ++ii)
        {
            int randomInt = Util::getRandomInt(0, 10);
            ++countsPerInts[randomInt];
        }

        REQUIRE(countsPerInts.size() == 11);

        for(const auto& countPerInt : countsPerInts)
        {
            REQUIRE(( (countPerInt.second <= 1050) && (countPerInt.second >= 750) ));
        }
    }

    SECTION("Returns numbers in the range [0, 10].")
    {
        vector<int> randomInts = Util::getRandomInt(0, 10, 10000);
        unordered_map<int, int> countsPerInts{};
        for(const int& num : randomInts)
        {
            ++countsPerInts[num];
        }

        REQUIRE(countsPerInts.size() == 11);

        for(const auto& countPerInt : countsPerInts)
        {
            REQUIRE(( (countPerInt.second <= 1000) && (countPerInt.second >= 800) ));
        }
    }
    
    SECTION("Returns a random true or false.")
    {
        
        unordered_map<bool, int> countsPerBools{};
        for(int ii=0; ii<10000; ++ii)
        {
            bool randomBool = Util::getRandomBool();
            ++countsPerBools[randomBool];
        }

        REQUIRE(countsPerBools.size() == 2);

        for(const auto& countPerBool: countsPerBools)
        {
            REQUIRE(( (countPerBool.second <= 5200) && (countPerBool.second >= 4800) ));
        }
    }


    SECTION("Returns Positions that are in the rectangle outlined by the given corners")
    {
        vector<Position> insideRectangle = Util::getRandomPositionsInRectangle(Rectangle{Position{0, 0}, Position{10, 10}}, 10000);
       
        unordered_map<int, int> countsPerXValues{};
        unordered_map<int, int> countsPerYValues{}; 
        for(Position pos : insideRectangle)
        {
            ++countsPerXValues[pos.getX()];
            ++countsPerYValues[pos.getY()];
        }
        
        REQUIRE(11 == countsPerXValues.size());
        REQUIRE(11 == countsPerYValues.size());

        for(const auto& countPerXValue : countsPerXValues)
        {
            REQUIRE(( (countPerXValue.second <= 1000) && (countPerXValue.second >= 800) ));
            REQUIRE(( (countPerXValue.second <= 1000) && (countPerXValue.second >= 800) ));
        }

        for(const auto& countPerYValue : countsPerYValues)
        {
            REQUIRE(( (countPerYValue.second <= 1000) && (countPerYValue.second >= 800) ));
            REQUIRE(( (countPerYValue.second <= 1000) && (countPerYValue.second >= 800) ));
        }
    }

    SECTION("Returns Positions that are in the rectangle outlined by cornerA and cornerB")
    {
        unordered_map<int, int> countsPerXValues{};
        unordered_map<int, int> countsPerYValues{};

        for(int ii=0; ii<10000; ++ii)
        {
            Position randomPosition = Util::getRandomPositionInRectangle(Rectangle{Position{0, 0}, Position{10, 10}});
            ++countsPerXValues[randomPosition.getX()];
            ++countsPerYValues[randomPosition.getY()];
        }
        
        REQUIRE(11 == countsPerXValues.size());
        REQUIRE(11 == countsPerYValues.size());

        for(const auto& countPerXValue : countsPerXValues)
        {
            REQUIRE(( (countPerXValue.second <= 1100) && (countPerXValue.second >= 800) ));
            REQUIRE(( (countPerXValue.second <= 1100) && (countPerXValue.second >= 800) ));
        }

        for(const auto& countPerYValue : countsPerYValues)
        {
            REQUIRE(( (countPerYValue.second <= 1000) && (countPerYValue.second >= 800) ));
            REQUIRE(( (countPerYValue.second <= 1000) && (countPerYValue.second >= 800) ));
        }
    }
    // TODO move to MainSetup Tests
    /*
    SECTION("Returns a vector of boxes with 10 groups, each of size 5")
    {
        vector<Box> boxes = Util::getBoxes(100, 10, 5);
        for(int ii=0; ii<boxes.size(); ++ii)
        {
            REQUIRE(boxes[ii] == Box{100 + ii, ii%10, 3, 3});
        }
    }
    */
}
