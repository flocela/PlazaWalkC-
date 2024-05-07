#include "catch.hpp"
#include "../src/Box.h"

#include <unordered_set>

using namespace std;

TEST_CASE("Box_core::")
{
    SECTION("Copy Constructor")
    {
        Box boxA{0, 0, 1, 2};
        Box boxB{boxA};    
        
        REQUIRE(boxA == boxB);
    }

    SECTION("Assigment Constructor")
    {
        Box boxA{0, 0, 1, 2};
        Box boxB{std::move(boxA)};
        
        REQUIRE(boxA == boxB);
    }

    SECTION("Boxes with different ids are not equal '=='")
    {
        Box boxA{0, 0, 1, 2};
        Box boxB{5, 0, 1, 2};    
        
        REQUIRE_FALSE(boxA == boxB);
    }

    SECTION("Boxes with different heights are not equal '=='")
    {
        Box boxA{0, 0, 1, 2};
        Box boxB{0, 0, 5, 2};    
        
        REQUIRE_FALSE(boxA == boxB);
    }

    SECTION("Boxes with different groupIds are not equal '=='")
    {
        Box boxA{0, 1, 1, 2};
        Box boxB{0, 0, 1, 2};    
        
        REQUIRE_FALSE(boxA == boxB);
    }

    SECTION("Boxes with different widths are not equal '=='")
    {
        Box boxA{0, 0, 1, 2};
        Box boxB{0, 0, 1, 5};    
        
        REQUIRE_FALSE(boxA == boxB);
    }

    SECTION("Boxes with same id, group, width, and height are '=='")
    {
        Box boxA{0, 0, 1, 2};
        Box boxB{0, 0, 1, 2};    
        
        REQUIRE(boxA == boxB);
    }

    SECTION("Boxes with different levels are equal '=='")
    {
        Box boxA{0, 0, 1, 2};
        Box boxB{0, 0, 1, 2};    
        boxA.upLevel();
        
        REQUIRE(boxA == boxB);
    }

    SECTION("Box gives the correct BoxInfo when getInfo() is called")
    {
        Box boxA{10, 10, 3, 3};
        boxA.upLevel();
        REQUIRE(BoxInfo{10, 10, 3, 3, 1} == boxA.getInfo());
    }

    SECTION("Identical Boxes return the same hash")
    {
        hash<Box> hasher;
        Box boxA{0, 0, 0, 0};
        Box boxB{0, 0, 0, 0};

        REQUIRE(hasher(boxA) == hasher(boxB));

        
        Box boxC{1, 1, 2, 2};
        Box boxD{1, 1, 2, 2};

        REQUIRE(hasher(boxC) == hasher(boxD));
       
 
        Box boxE{10, 11, 12, 13};
        Box boxF{10, 11, 12, 13};

        REQUIRE(hasher(boxE) == hasher(boxF));
    }

    SECTION("Require that many boxes don't have the same hash")
    {
        hash<Box> hasher;

        unordered_set<size_t> hashNumbers{};
        for(int ii=0; ii<2; ++ii)
        {
            for(int jj=0; jj<2000; ++jj)
            {
                unsigned int hashNumber = hasher(Box{jj, ii, 3, 3});
                REQUIRE(hashNumbers.find(hashNumber) == hashNumbers.end());
                hashNumbers.insert(hashNumber);
            }
        }
    }
        
}
