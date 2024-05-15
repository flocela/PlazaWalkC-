#include "catch.hpp"
#include "../src/Drop.h"

#include <sstream>
#include <unordered_set>

using namespace std;

TEST_CASE("Drop_core::")
{
    SECTION("Copy Constructor")
    {
        Drop dropA{10, 11, 5, MoveType::to_arrive};
        dropA.setHasChanged(true); 
        Drop dropB{dropA};    
        
        REQUIRE(dropA == dropB);
    }

    SECTION("Assigment Constructor")
    {
        Drop dropA{10, 11, 5, MoveType::to_arrive};
        dropA.setHasChanged(true); 
        Drop dropB{std::move(dropA)};
        
        REQUIRE(dropA == dropB);
    }

    SECTION("Drops with different positions are not equal '=='.")
    {
        Drop drop{10, 11, 5, MoveType::to_arrive};
        drop.setHasChanged(true); 

        Drop dropDiffX{100, 11, 5, MoveType::to_arrive};
        dropDiffX.setHasChanged(true); 

        Drop dropDiffY{10, 110, 5, MoveType::to_arrive};
        dropDiffY.setHasChanged(true); 
        
        REQUIRE_FALSE(drop == dropDiffX);
        REQUIRE_FALSE(drop == dropDiffY);
    }

    SECTION("Drops with different MoveTypes are equal '=='.")
    {
        Drop drop{10, 11, 5, MoveType::to_arrive};
        drop.setHasChanged(true); 

        Drop dropDiffType{10, 11, 5, MoveType::arrive};
        dropDiffType.setHasChanged(true);

        REQUIRE(drop == dropDiffType);
    }

    SECTION("Drops with different hasChanged are equal '=='.")
    {
        Drop drop{10, 11, 5, MoveType::to_arrive};
        drop.setHasChanged(true); 

        Drop dropDiffHasChanged{10, 11, 5, MoveType::arrive};
        dropDiffHasChanged.setHasChanged(false);

        REQUIRE(drop == dropDiffHasChanged);
    }

    SECTION("Drops that are the same are equal '=='.")
    {
        Drop drop{10, 11, 5, MoveType::to_arrive};
        drop.setHasChanged(true); 

        Drop dropSame{10, 11, 5, MoveType::arrive};
        dropSame.setHasChanged(true);

        REQUIRE(drop == dropSame);
    }
    
    SECTION("Identical Drops return the same hash")
    {
        hash<Drop> hasher;
        Drop dropA{0, 0, 0, MoveType::left};
        Drop dropB{0, 0, 0, MoveType::left};

        REQUIRE(hasher(dropA) == hasher(dropB));
        
        Drop dropC{1, 1, 2, MoveType::to_arrive};
        Drop dropD{1, 1, 2, MoveType::to_arrive};

        REQUIRE(hasher(dropC) == hasher(dropD));
    }

    SECTION("Require that many Drops don't have the same hash")
    {
        hash<Drop> hasher;

        unordered_set<size_t> hashNumbers{};
        for(int ii=0; ii<100; ++ii)
        {
            for(int jj=0; jj<100; ++jj)
            {
                unsigned int hashNumber = hasher(Drop{jj, ii, 1, MoveType::left});
                if(hashNumbers.find(hashNumber) != hashNumbers.end())
                {
                    cout << Drop{jj, ii, 1, MoveType::left} << endl;
                }
                REQUIRE(hashNumbers.find(hashNumber) == hashNumbers.end());
                hashNumbers.insert(hashNumber);
            }
        }
    }
    
    SECTION("test ostream operator")
    {
        Drop drop{10, 11, 5, MoveType::to_arrive};
        stringstream out;
        out << drop;
        REQUIRE("Drop: [{10, 11}, 5, MoveType::to_arrive, false]" == out.str());
    }
}
