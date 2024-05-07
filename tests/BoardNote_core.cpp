#include "catch.hpp"

#include "../src/BoardNote.h"
#include <unordered_set>

using namespace std;

TEST_CASE("BoardNote_core::")
{
    SECTION("BoardNote returns type")
    {
        BoardNote note{22, SpotType::to_leave};
        REQUIRE(SpotType::to_leave == note.getType());
    }

    SECTION("BoardNote returns boxId")
    {
        BoardNote note{22, SpotType::arrive};
        REQUIRE(22 == note.getBoxId());
    }

    SECTION("BoardNote == operator returns true")
    {
        BoardNote note1{22, SpotType::left};
        BoardNote note2{22, SpotType::left}; 
        REQUIRE(note1 == note2);
    }

    SECTION("BoardNote == operator returns false if boxId's are different")
    {
        BoardNote note1{22, SpotType::left};
        BoardNote note2{24, SpotType::left}; 
        REQUIRE_FALSE(note1 == note2);
    }

    SECTION("BoardNote == operator returns false if type's are different")
    {
        BoardNote note1{22, SpotType::left};
        BoardNote note2{22, SpotType::to_arrive}; 
        REQUIRE_FALSE(note1 == note2);
    }
    
    SECTION("Identical BoardNotes return the same hash")
    {
        hash<BoardNote> hasher;
        BoardNote boardInfoA{0, SpotType::to_arrive};
        BoardNote boardInfoB{0, SpotType::to_arrive};

        REQUIRE(hasher(boardInfoA) == hasher(boardInfoB));
        
        BoardNote boardInfoC{1, SpotType::arrive};
        BoardNote boardInfoD{1, SpotType::arrive};

        REQUIRE(hasher(boardInfoC) == hasher(boardInfoD));
        
        BoardNote boardInfoE{10, SpotType::to_leave};
        BoardNote boardInfoF{10, SpotType::to_leave};

        REQUIRE(hasher(boardInfoE) == hasher(boardInfoF));
    }

    SECTION("Require that many BoardNotes don't have the same hash")
    {
        hash<BoardNote> hasher;

        unordered_set<size_t> hashNumbers{};
        for(int ii=0; ii<2000; ++ii)
        {
            for(int jj=1; jj<=1; ++jj)
            {
                unsigned int hashNumber = hasher(BoardNote{ii, static_cast<SpotType>(jj)});
                REQUIRE(hashNumbers.find(hashNumber) == hashNumbers.end());
                hashNumbers.insert(hashNumber);
            }
        }
    }

}
