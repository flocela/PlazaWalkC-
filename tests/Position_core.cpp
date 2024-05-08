#include "catch.hpp"
#include "../src/Position.h"

#include <sstream>
#include <unordered_set>


using namespace std;

TEST_CASE("Position_core::")
{
    SECTION("construct a Position")
    {
        Position p{10, 12};
        
        REQUIRE(p.getX() == 10);
        REQUIRE(p.getY() == 12);
    }

    SECTION("operator== returns false when x-value in Position is different")
    {
        Position p{10, 12};
        Position op{1000, 12};
        
        REQUIRE_FALSE(p == op);
    }

    SECTION("operator== returns false when y-value in Position is different")
    {
        Position p{10, 12};
        Position op{10, 1200};
        
        REQUIRE_FALSE(p == op);
    }

    SECTION("operator== returns true when positions are equal")
    {
        Position p{10, 12};
        Position op{10, 12};
        
        REQUIRE(p == op);
    }

    SECTION("toString()")
    {
        Position p{101, 202};
        REQUIRE("{101, 202}" == p.toString());
    }

    SECTION("ostream operator")
    {
        Position p{1000, 1200};
       
        ostringstream oss;
        oss << p; 
        REQUIRE(oss.str() == "{1000, 1200}");
    }
    
    SECTION("Identical Positions return the same hash")
    {
        hash<Position> hasher;
        Position positionA{0, 0};
        Position positionB{0, 0};

        REQUIRE(hasher(positionA) == hasher(positionB));
        
        Position positionC{1, 1};
        Position positionD{1, 1};

        REQUIRE(hasher(positionC) == hasher(positionD));
        
        Position positionE{10, 11};
        Position positionF{10, 11};

        REQUIRE(hasher(positionE) == hasher(positionF));
    }

    SECTION("Require that many positiones don't have the same hash")
    {
        hash<Position> hasher;

        unordered_set<size_t> hashNumbers{};
        for(int ii=0; ii<100; ++ii)
        {
            for(int jj=0; jj<100; ++jj)
            {
                unsigned int hashNumber = hasher(Position{ii, jj});
                REQUIRE(hashNumbers.find(hashNumber) == hashNumbers.end());
                hashNumbers.insert(hashNumber);
            }
        }
    }
}
