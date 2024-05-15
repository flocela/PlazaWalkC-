#include "catch.hpp"
#include "../src/Spot.h"

using namespace std;
/*
TEST_CASE("Spot_core::")
{

    SECTION("Copy Constructor")
    {
        Position pos{3, 4};
        Spot spot{pos};
        spot.changeNote(BoardNote{10, MoveType::to_arrive});

        Spot spotCopy = spot;
        
        REQUIRE(spot.getPosition() == spotCopy.getPosition());
        REQUIRE(spot.getBoardNote() == spotCopy.getBoardNote());
    }

    SECTION("Move Constructor")
    {
        Position pos{3, 4};
        Spot spot{pos};
        spot.changeNote(BoardNote{10, MoveType::to_arrive});

        Spot spot2(std::move(spot));
     
        REQUIRE(spot2.getPosition() == spot.getPosition());
        REQUIRE(spot2.getBoardNote() == spot.getBoardNote());
    }

    SECTION("Spot is constructed and should be in a default state.")
    {
        Position pos{3, 4};
        Spot spot{pos};

        SECTION("Returns the Position given in the constructor.")
        {
            REQUIRE(pos == spot.getPosition());
        }
        
        SECTION("Returns the default type and default boxId.")
        {
            REQUIRE(-1 == spot.getBoardNote().getBoxId());
            REQUIRE(MoveType::left == spot.getBoardNote().getType());
        }
    }

    SECTION("Spot originally does not hold a box (is MoveType::left)")
    {
        Spot spot{Position{100, 200}};

        SECTION("and receives note with MoveType::to_arrive, then spot will contain the new box_id and MoveType::to_arrive.")
        {
            // Box with boxId 10 is about to arrive.

            Spot spot{Position{8, 9}};
            pair<int, bool> successPair = spot.changeNote(BoardNote{10, MoveType::to_arrive});
           
            REQUIRE(-1 == successPair.first);
            REQUIRE(true == successPair.second); 
            REQUIRE(10 == spot.getBoardNote().getBoxId());
            REQUIRE(MoveType::to_arrive == spot.getBoardNote().getType());
        }
       
        SECTION("and receives note with MoveType::arrive, then an exception is thrown. Spot's type must be MoveType::to_arrive to accept a MoveType::arrive note.")
        {   
            // Box with boxId 10 arrives.

            REQUIRE_THROWS(spot.changeNote(BoardNote{10, MoveType::arrive}));
            REQUIRE(-1 == spot.getBoardNote().getBoxId());
            REQUIRE(MoveType::left == spot.getBoardNote().getType());
        }
        
        SECTION("and receives an MoveType::to_leave, then an exception is thrown. Spot's type must be MoveType::arrive to accept MoveType::to_leave.")
        {
            // Box with boxId 10 is about to leave.
            
            REQUIRE_THROWS(spot.changeNote(BoardNote{10, MoveType::to_leave}));
            REQUIRE(-1 == spot.getBoardNote().getBoxId());
            REQUIRE(MoveType::left == spot.getBoardNote().getType());
        }
        
        SECTION("and recieves a MoveType::left, then an exception is thrown. Spot's type must be MoveType::to_leave before accepting MoveType::left.")
        {
            // Box with boxId 10 leaves.

            REQUIRE_THROWS(spot.changeNote(BoardNote{10, MoveType::left}));
            REQUIRE(-1 == spot.getBoardNote().getBoxId());
            REQUIRE(MoveType::left == spot.getBoardNote().getType());
        }
    }

    SECTION("Spot originally has the type MoveType::to_leave")
    {
        // Box with boxId 10 is about to leave.
        Spot spot{Position{100, 200}};
        spot.changeNote(BoardNote{10, MoveType::to_arrive});
        spot.changeNote(BoardNote{10, MoveType::arrive});
        spot.changeNote(BoardNote{10, MoveType::to_leave});

        SECTION("and receives a note with the with the same boxId")
        {
            SECTION("and receives a MoveType::to_leave, then an exception is thrown. The Spot's type is MoveType::left.")
            {
                // Box with boxId 10 is about to leave.
                REQUIRE_THROWS(spot.changeNote(BoardNote{10, MoveType::to_leave}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_leave == spot.getBoardNote().getType());
            }
            
            SECTION("and receives a MoveType::to_arrive, then an exception is thrown.")
            {
                // Box with boxId 10 is about to arrive.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, MoveType::to_arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_leave == spot.getBoardNote().getType());
            }

            SECTION("and receives a MoveType::left, then the Spot's boxId will change to -1, and type will be MoveType::left.")
            {
                // Box with boxId 10 leaves.
                pair<int, bool> successPair = spot.changeNote(BoardNote{10, MoveType::left});

                REQUIRE(10 == successPair.first);
                REQUIRE(true == successPair.second); 
                REQUIRE(-1 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::left == spot.getBoardNote().getType());
            }
            
            SECTION("and receives a MoveType::arrive, then an exception is thrown.")
            {
                // Box with boxId 10 arrives.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, MoveType::arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_leave == spot.getBoardNote().getType());
            }
        }

        SECTION("and receives a note with the with a different boxId")
        {
            SECTION("and a MoveType::to_leave, then an exception is thrown.")
            {
                // Box with boxId 99 is about to leave.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, MoveType::to_leave}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_leave == spot.getBoardNote().getType());
            }
            
            SECTION("and receives MoveType::to_arrive, then false is returned.")
            {
                // Box with boxId 99 is about to arrive.
                pair<int, bool> successPair = spot.changeNote(BoardNote({99, MoveType::to_arrive}));

                REQUIRE(10 == successPair.first);
                REQUIRE(false == successPair.second); 

                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_leave == spot.getBoardNote().getType());
            }

            SECTION("and a MoveType::left, then an exception is thrown.")
            {
                // Box with boxId 99 leaves.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, MoveType::left}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_leave == spot.getBoardNote().getType());
            }
            
            SECTION("and receives a MoveType::left, then an exception is thrown.")
            {
                // Box with boxId 99 arrives.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, MoveType::arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_leave == spot.getBoardNote().getType());
            }
        }
    }

    SECTION("Spot:: Spot originally has the type MoveType::to_arrive")
    {
        // Box with boxId 10 is about to arrive.
        Spot spot{Position{100, 200}};
        spot.changeNote(BoardNote{10, MoveType::to_arrive});

        SECTION("and receives a note with the same boxId")
        {
            SECTION("and MoveType::to_arrive, then an exception is thrown.")
            {
                // Box with boxId 10 is about to leave.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, MoveType::to_leave}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_arrive == spot.getBoardNote().getType());
            }
            
            SECTION("and MoveType::to_arrive, then an exception is thrown.")
            {
                // Box with boxId 10 is about to arrive.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, MoveType::to_arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_arrive == spot.getBoardNote().getType());
            }

            SECTION("and MoveType::left, then an exception is thrown.")
            {
                // Box with boxId 10 leaves.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, MoveType::left}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_arrive == spot.getBoardNote().getType());
            }
            
            SECTION("and MoveType::arrive, then Spot's type with change to MoveType::arrive.")
            {
                // Box with boxId 10 arrives.
                pair<int, bool> successPair = spot.changeNote(BoardNote{10, MoveType::arrive});
                
                REQUIRE(10 == successPair.first);
                REQUIRE(true == successPair.second);
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::arrive == spot.getBoardNote().getType());
            }

        }
        
        SECTION("and receives a note with a different box (different boxId)")
        {
            SECTION("and MoveType::to_leave, then an exception is thrown.")
            {
                // Box with boxId 99 is about to leave.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, MoveType::to_leave}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_arrive == spot.getBoardNote().getType());
            }
            
            SECTION("and MoveType::to_arrive, then false is returned.")
            {
                // Box with boxId 99 is about to arrive.
                pair<int, bool> successPair = spot.changeNote(BoardNote{99, MoveType::to_arrive});

                REQUIRE(10 == successPair.first);
                REQUIRE(false == successPair.second);
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_arrive == spot.getBoardNote().getType());
            }

            SECTION("and MoveType::left, then an exception is thrown.")
            {
                // Box with boxId 99 leaves.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, MoveType::left}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_arrive == spot.getBoardNote().getType());
            }
            
            SECTION("and MoveType::arrive, then an exception is thrown.")
            {
                // Box with boxId 99 arrives.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, MoveType::arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_arrive == spot.getBoardNote().getType());
            }
        }
    }

    SECTION("Spot:: Spot originally has the type MoveType::arrive")
    {
        // Box with boxId 10 has arrived.
        Spot spot{Position{100, 200}};
        spot.changeNote(BoardNote{10, MoveType::to_arrive});
        spot.changeNote(BoardNote{10, MoveType::arrive});

        SECTION("and receives a note with the same boxId")
        {
            SECTION("and MoveType::to_leave, then the Spot's type will change to MoveType::to_leave.")
            {
                // Box with boxId 10 is about to leave.
                pair<int, bool> successPair = spot.changeNote(BoardNote{10, MoveType::to_leave});

                REQUIRE(10 == successPair.first);
                REQUIRE(true == successPair.second);
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::to_leave == spot.getBoardNote().getType());
            }
            
            SECTION("and MoveType::to_arrive, then an exception is thrown.")
            {
                // Box with boxId 10 is about to arrive.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, MoveType::to_arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::arrive == spot.getBoardNote().getType());
            }

            SECTION("and MoveType::left, then an exception is thrown.")
            {
                // Box with boxId 10 leaves.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, MoveType::left}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::arrive == spot.getBoardNote().getType());
            }
            
            SECTION("and MoveType::arrive, then an exception is thrown.")
            {
                // Box with boxId 10 arrives.

                REQUIRE_THROWS(spot.changeNote(BoardNote{10, MoveType::arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::arrive == spot.getBoardNote().getType());
            }
        }

        SECTION("and receives a note with a different box (different boxId)")
        {
            SECTION("and MoveType::to_leave, then an exception is thrown.")
            {
                // Box with boxId 99 is about to leave.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, MoveType::to_leave}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::arrive == spot.getBoardNote().getType());
            }

            SECTION("and MoveType::to_arrive, then false is returned.")
            {
                // Box with boxId 99 is about to arrive.
                pair<int, bool> successPair = spot.changeNote(BoardNote{99, MoveType::to_arrive});

                REQUIRE(10 == successPair.first);
                REQUIRE(false == successPair.second);
            }

            SECTION("and MoveType::left, then an exception is thrown.")
            {
                // Box with boxId 99 leaves.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, MoveType::left}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::arrive == spot.getBoardNote().getType());
            }
            
            SECTION("and MoveType::arrive, then an exception is thrown.")
            {
                // boxId 99 arrives.

                REQUIRE_THROWS(spot.changeNote(BoardNote{99, MoveType::arrive}));
                REQUIRE(10 == spot.getBoardNote().getBoxId());
                REQUIRE(MoveType::arrive == spot.getBoardNote().getType());
            }

        }
    }

    SECTION("Verify that SpotListeners are notified when there is a successful changeNote()")
    {
        Spot spot{Position{100, 200}};
        SpotListener spotListener{};
        spot.registerListener(&spotListener);
        spot.changeNote(BoardNote{10, MoveType::to_arrive});
        spot.changeNote(BoardNote{10, MoveType::arrive});

        vector<string> successfulNotes =spotListener.getStateStrings();
        REQUIRE("B10, MoveType::to_arrive" == successfulNotes[0]);
        REQUIRE("B10, MoveType::arrive" == successfulNotes[1]);
    }
         
}
*/
