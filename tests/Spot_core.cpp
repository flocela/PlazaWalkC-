#include "catch.hpp"
#include <iostream>
#include "../src/Spot.h"
#include <regex>
#include <thread>

using namespace std;
TEST_CASE("Spot_core::")
{

    SECTION("Copy Constructor")
    {
        Position pos{3, 4};
        Spot spot{pos};
        spot.changeNote(BoardNote{10, SpotType::to_arrive});

        Spot spotCopy = spot;
        
        REQUIRE(spot.getPosition() == spotCopy.getPosition());
        REQUIRE(spot.getBoardNote() == spotCopy.getBoardNote());
    }

    SECTION("Move Constructor")
    {
        Position pos{3, 4};
        Spot spot{pos};
        spot.changeNote(BoardNote{10, SpotType::to_arrive});

        Spot spot2(std::move(spot));
     
        REQUIRE(spot2.getPosition() == spot.getPosition());
        REQUIRE(spot2.getBoardNote() == spot.getBoardNote());
    }

    SECTION("Spot is constructed and should be in a default state.")
    {
        // Construct Spot.
        Position pos{3, 4};
        Spot spot{pos};

        SECTION("Returns the Position given in the constructor.")
        {
            REQUIRE(pos == spot.getPosition());
        }
        
        SECTION("Returns the default type and default boxId.")
        {
            REQUIRE(-1 == spot.getBoardNote().getBoxId());
            REQUIRE(SpotType::left == spot.getBoardNote().getType());
        }
    }

    SECTION("Spot originally does not hold a box (is SpotType::left)")
    {
        Spot spot{Position{100, 200}};

        SECTION("and receives note with SpotType::to_arrive, then spot will contain the new box_id and SpotType::to_arrive.")
        {
            // Box with boxId 10 is about to arrive.

            Spot spot{Position{8, 9}};
            pair<int, bool> successPair = spot.changeNote(BoardNote{10, SpotType::to_arrive});
           
            REQUIRE(-1 == successPair.first);
            REQUIRE(true == successPair.second); 
            REQUIRE(10 == spot.getBoardNote().getBoxId());
            REQUIRE(SpotType::to_arrive == spot.getBoardNote().getType());
        }
       
        SECTION("and receives note with SpotType::arrive, then an exception is thrown. Spot's type must be SpotType::to_arrive to accept a SpotType::arrive note.")
        {   
            // Box with boxId 10 arrives.

            REQUIRE_THROWS(spot.changeNote(BoardNote{10, SpotType::arrive}));
            REQUIRE(-1 == spot.getBoardNote().getBoxId());
            REQUIRE(SpotType::left == spot.getBoardNote().getType());
        }
        
        SECTION("and receives an SpotType::to_leave, then an exception is thrown. Spot's type must be SpotType::arrive to accept SpotType::to_leave.")
        {
            // Box with boxId 10 is about to leave.
            
            REQUIRE_THROWS(spot.changeNote(BoardNote{10, SpotType::to_leave}));
            REQUIRE(-1 == spot.getBoardNote().getBoxId());
            REQUIRE(SpotType::left == spot.getBoardNote().getType());
        }
        
        SECTION("and recieves a SpotType::left, then an exception is thrown. Spot's type must be SpotType::to_leave before accepting SpotType::left.")
        {
            // Box with boxId 10 leaves.

            REQUIRE_THROWS(spot.changeNote(BoardNote{10, SpotType::left}));
            REQUIRE(-1 == spot.getBoardNote().getBoxId());
            REQUIRE(SpotType::left == spot.getBoardNote().getType());
        }
    }

    SECTION("Spot originally has the type SpotType::to_leave")
    {
        // Box with boxId 10 is about to leave.
        Spot spot{Position{100, 200}};
        spot.changeNote(BoardNote{10, SpotType::to_arrive});
        spot.changeNote(BoardNote{10, SpotType::arrive});
        spot.changeNote(BoardNote{10, SpotType::to_leave});

        SECTION("and receives a note with the with the same boxId")
        {
            SECTION("and receives a SpotType::to_leave, then an exception is thrown. The Spot's type is SpotType::left.")
            {
                // Box with boxId 10 is about to leave.
                REQUIRE_THROWS(spot.changeNote(BoardNote{10, SpotType::to_leave}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_leave == spot.getBoardNote().getType());
            }
            
            SECTION("and receives a SpotType::to_arrive, then an exception is thrown.")
            {
                // Box with boxId 10 is about to arrive.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, SpotType::to_arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_leave == spot.getBoardNote().getType());
            }

            SECTION("and receives a SpotType::left, then the Spot's boxId will change to -1, and type will be SpotType::left.")
            {
                // Box with boxId 10 leaves.
                pair<int, bool> successPair = spot.changeNote(BoardNote{10, SpotType::left});

                REQUIRE(10 == successPair.first);
                REQUIRE(true == successPair.second); 
                REQUIRE(-1 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::left == spot.getBoardNote().getType());
            }
            
            SECTION("and receives a SpotType::arrive, then an exception is thrown.")
            {
                // Box with boxId 10 arrives.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, SpotType::arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_leave == spot.getBoardNote().getType());
            }
        }

        SECTION("and receives a note with the with a different boxId")
        {
            SECTION("and a SpotType::to_leave, then an exception is thrown.")
            {
                // Box with boxId 99 is about to leave.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, SpotType::to_leave}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_leave == spot.getBoardNote().getType());
            }
            
            SECTION("and receives SpotType::to_arrive, then false is returned.")
            {
                // Box with boxId 99 is about to arrive.
                pair<int, bool> successPair = spot.changeNote(BoardNote({99, SpotType::to_arrive}));

                REQUIRE(10 == successPair.first);
                REQUIRE(false == successPair.second); 

                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_leave == spot.getBoardNote().getType());
            }

            SECTION("and a SpotType::left, then an exception is thrown.")
            {
                // Box with boxId 99 leaves.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, SpotType::left}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_leave == spot.getBoardNote().getType());
            }
            
            SECTION("and receives a SpotType::left, then an exception is thrown.")
            {
                // Box with boxId 99 arrives.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, SpotType::arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_leave == spot.getBoardNote().getType());
            }
        }
    }

    SECTION("Spot:: Spot originally has the type SpotType::to_arrive")
    {
        // Box with boxId 10 is about to arrive.
        Spot spot{Position{100, 200}};
        spot.changeNote(BoardNote{10, SpotType::to_arrive});

        SECTION("and receives a note with the same boxId")
        {
            SECTION("and SpotType::to_arrive, then an exception is thrown.")
            {
                // Box with boxId 10 is about to leave.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, SpotType::to_leave}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_arrive == spot.getBoardNote().getType());
            }
            
            SECTION("and SpotType::to_arrive, then an exception is thrown.")
            {
                // Box with boxId 10 is about to arrive.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, SpotType::to_arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_arrive == spot.getBoardNote().getType());
            }

            SECTION("and SpotType::left, then an exception is thrown.")
            {
                // Box with boxId 10 leaves.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, SpotType::left}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_arrive == spot.getBoardNote().getType());
            }
            
            SECTION("and SpotType::arrive, then Spot's type with change to SpotType::arrive.")
            {
                // Box with boxId 10 arrives.
                pair<int, bool> successPair = spot.changeNote(BoardNote{10, SpotType::arrive});
                
                REQUIRE(10 == successPair.first);
                REQUIRE(true == successPair.second);
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::arrive == spot.getBoardNote().getType());
            }

        }
        
        SECTION("and receives a note with a different box (different boxId)")
        {
            SECTION("and SpotType::to_leave, then an exception is thrown.")
            {
                // Box with boxId 99 is about to leave.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, SpotType::to_leave}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_arrive == spot.getBoardNote().getType());
            }
            
            SECTION("and SpotType::to_arrive, then false is returned.")
            {
                // Box with boxId 99 is about to arrive.
                pair<int, bool> successPair = spot.changeNote(BoardNote{99, SpotType::to_arrive});

                REQUIRE(10 == successPair.first);
                REQUIRE(false == successPair.second);
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_arrive == spot.getBoardNote().getType());
            }

            SECTION("and SpotType::left, then an exception is thrown.")
            {
                // Box with boxId 99 leaves.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, SpotType::left}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_arrive == spot.getBoardNote().getType());
            }
            
            SECTION("and SpotType::arrive, then an exception is thrown.")
            {
                // Box with boxId 99 arrives.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, SpotType::arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_arrive == spot.getBoardNote().getType());
            }
        }
    }

    SECTION("Spot:: Spot originally has the type SpotType::arrive")
    {
        // Box with boxId 10 has arrived.
        Spot spot{Position{100, 200}};
        spot.changeNote(BoardNote{10, SpotType::to_arrive});
        spot.changeNote(BoardNote{10, SpotType::arrive});

        SECTION("and receives a note with the same boxId")
        {
            SECTION("and SpotType::to_leave, then the Spot's type will change to SpotType::to_leave.")
            {
                // Box with boxId 10 is about to leave.
                pair<int, bool> successPair = spot.changeNote(BoardNote{10, SpotType::to_leave});

                REQUIRE(10 == successPair.first);
                REQUIRE(true == successPair.second);
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::to_leave == spot.getBoardNote().getType());
            }
            
            SECTION("and SpotType::to_arrive, then an exception is thrown.")
            {
                // Box with boxId 10 is about to arrive.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, SpotType::to_arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::arrive == spot.getBoardNote().getType());
            }

            SECTION("and SpotType::left, then an exception is thrown.")
            {
                // Box with boxId 10 leaves.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, SpotType::left}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::arrive == spot.getBoardNote().getType());
            }
            
            SECTION("and SpotType::arrive, then an exception is thrown.")
            {
                // Box with boxId 10 arrives.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, SpotType::arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::arrive == spot.getBoardNote().getType());
            }
        }

        SECTION("and receives a note with a different box (different boxId)")
        {
            SECTION("and SpotType::to_leave, then an exception is thrown.")
            {
                // Box with boxId 99 is about to leave.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, SpotType::to_leave}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::arrive == spot.getBoardNote().getType());
            }

            SECTION("and SpotType::to_arrive, then false is returned.")
            {
                // Box with boxId 99 is about to arrive.
                pair<int, bool> successPair = spot.changeNote(BoardNote{99, SpotType::to_arrive});

                REQUIRE(10 == successPair.first);
                REQUIRE(false == successPair.second);
            }

            SECTION("and SpotType::left, then an exception is thrown.")
            {
                // Box with boxId 99 leaves.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, SpotType::left}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::arrive == spot.getBoardNote().getType());
            }
            
            SECTION("and SpotType::arrive, then an exception is thrown.")
            {
                // boxId 99 arrives.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, SpotType::arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(SpotType::arrive == spot.getBoardNote().getType());
            }

        }
    }
}
