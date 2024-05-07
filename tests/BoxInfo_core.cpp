#include "catch.hpp"
#include "../src/BoxInfo.h"

#include <thread>
#include <unordered_set>

using namespace std;

TEST_CASE("BoxInfo_core::")
{
    SECTION("Copy Constructor")
    {
        BoxInfo boxInfoA{0, 0, 1, 2, 3};
        BoxInfo boxInfoB{boxInfoA};    
        
        REQUIRE(boxInfoA == boxInfoB);
    }

    SECTION("Assigment Constructor")
    {
        BoxInfo boxInfoA{0, 0, 1, 2, 3};
        BoxInfo boxInfoB{std::move(boxInfoA)};
        
        REQUIRE(boxInfoA == boxInfoB);
    }

    SECTION("BoxInfos with different ids are not equal '=='")
    {
        BoxInfo boxInfoA{0, 0, 1, 2, 0};
        BoxInfo boxInfoB{5, 0, 1, 2, 0};    
        
        REQUIRE_FALSE(boxInfoA == boxInfoB);
    }

    SECTION("BoxInfos with different groupIds are not equal '=='")
    {
        BoxInfo boxInfoA{5, 2, 1, 2, 0};
        BoxInfo boxInfoB{5, 0, 1, 2, 0};    
        
        REQUIRE_FALSE(boxInfoA == boxInfoB);
    }

    SECTION("BoxInfos with different heights are not equal '=='")
    {
        BoxInfo boxInfoA{0, 0, 1, 2, 0};
        BoxInfo boxInfoB{0, 0, 5, 2, 0};    
        
        REQUIRE_FALSE(boxInfoA == boxInfoB);
    }

    SECTION("BoxInfos with different widths are not equal '=='")
    {
        BoxInfo boxInfoA{0, 0, 1, 2, 0};
        BoxInfo boxInfoB{0, 0, 1, 5, 0};    
        
        REQUIRE_FALSE(boxInfoA == boxInfoB);
    }
    
    SECTION("BoxInfos with different levels are not equal '=='")
    {
        BoxInfo boxInfoA{0, 0, 1, 2, 3};
        BoxInfo boxInfoB{0, 0, 1, 2, 4};    
        
        REQUIRE_FALSE(boxInfoA == boxInfoB);
    }

    SECTION("BoxInfos with same id, group, width, height, and level are '=='")
    {
        BoxInfo boxInfoA{4, 0, 1, 2, 3};
        BoxInfo boxInfoB{4, 0, 1, 2, 3};    
        
        REQUIRE(boxInfoA == boxInfoB);
    }
    
    SECTION("Identical BoxInfos return the same hash")
    {
        hash<BoxInfo> hasher;
        BoxInfo boxInfoA{0, 0, 0, 0, 0};
        BoxInfo boxInfoB{0, 0, 0, 0, 0};

        REQUIRE(hasher(boxInfoA) == hasher(boxInfoB));
        
        BoxInfo boxInfoC{1, 1, 2, 2, 3};
        BoxInfo boxInfoD{1, 1, 2, 2, 3};

        REQUIRE(hasher(boxInfoC) == hasher(boxInfoD));
        
        BoxInfo boxInfoE{10, 11, 12, 13, 14};
        BoxInfo boxInfoF{10, 11, 12, 13, 14};

        REQUIRE(hasher(boxInfoE) == hasher(boxInfoF));
    }

    SECTION("Require that many BoxInfos don't have the same hash")
    {
        hash<BoxInfo> hasher;

        unordered_set<size_t> hashNumbers{};
        for(int ii=0; ii<2; ++ii)
        {
            for(int jj=0; jj<2000; ++jj)
            {
                unsigned int hashNumber = hasher(BoxInfo{jj, ii, 3, 3, 0});
                REQUIRE(hashNumbers.find(hashNumber) == hashNumbers.end());
                hashNumbers.insert(hashNumber);
            }
        }
    }
}
