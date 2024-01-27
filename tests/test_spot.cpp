#include "catch.hpp"
#include <iostream>
#include "../src/Spot.h"

using namespace std;

TEST_CASE("Spot:: Spot is constructed and should be in a default state.")
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
        REQUIRE(-1 == spot.getType());
        REQUIRE(-1 == spot.getBoxId());
    }
}

TEST_CASE("Spot:: Spot originally does not hold a box)")
{
    Spot spot{Position{100, 200}};

    SECTION("and receives an 'Imminent Arrival' note, then spot will contain the new box_id and type 2.")
    {
        // Box with boxId 10 is about to arrive.
        // 'Imminent Arrival' type is 2.
        BoardNote imminentArrivalNote{10, 2};

        Spot spot{Position{8, 9}};
        spot.tagNote(imminentArrivalNote);
        
        REQUIRE(10 == spot.getBoxId());
        REQUIRE(2 == spot.getType());
    }
   
    SECTION("and receives an 'Arrival' note, then an exception is thrown. Spot's type must be 'Imminent Arrival' type to accept an 'Arrival' note.")
    {   
        // Box with boxId 10 arrives.
        // 'Arrives' type is 4.
        BoardNote arrivalNote{10, 4};

        REQUIRE_THROWS(spot.tagNote(arrivalNote));
        REQUIRE(-1 == spot.getBoxId());
        REQUIRE(-1 == spot.getType());
    }
    
    SECTION("and receives an 'Imminent Departure' note, then an exception is thrown. Spot's type must be'Arrived' type to accept an 'Imminent Departure' note.")
    {
        // Box with boxId 10 is about to leave.
        // 'Imminent Departure' type is 1.
        BoardNote imminentDepartureNote{10, 1};

        REQUIRE_THROWS(spot.tagNote(imminentDepartureNote));
        REQUIRE(-1 == spot.getBoxId());
        REQUIRE(-1 == spot.getType());
    }
    
    SECTION("and recieves a 'Departure' note, then an exception is thrown. Spot's type must be 'Imminent Departure' type before accepting a 'Departure' note.")
    {
        // Box with boxId 10 leaves.
        // 'Departure' type is 3.
        BoardNote departureNote{10, 3};

        REQUIRE_THROWS(spot.tagNote(departureNote));
        REQUIRE(-1 == spot.getBoxId());
        REQUIRE(-1 == spot.getType());
    }
}

TEST_CASE("Spot:: Spot originally has the type 'Imminent Departure'")
{
    // Box with boxId 10 is about to leave.
    // 'Imminently Departure' type is 1.
    BoardNote imminentArrivalNote{10, 2};
    BoardNote arrivalNote{10, 4};
    BoardNote imminentDepartureNote{10, 1};
    Spot spot{Position{100, 200}};
    spot.tagNote(imminentArrivalNote);
    spot.tagNote(arrivalNote);
    spot.tagNote(imminentDepartureNote);

    SECTION("and receives a note with the with the same boxId")
    {
        SECTION("and an 'Imminent Departure' type, then an exception is thrown. The Spot's type is already 'Imminent Departure.")
        {
            // Box with boxId 10 is about to leave.
            // 'Imminent Departure' type is 1.
            BoardNote imminentDepartureNote{10, 1};
            REQUIRE_THROWS(spot.tagNote(imminentDepartureNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(1 == spot.getType());
        }
        
        SECTION("and an 'Imminent Arrival' type, then an exception is thrown. The Spot's type must be The box can not be about to arrive, it has already arrived and is about to leave.")
        {
            // Box with boxId 10 is about to arrive.
            // 'Imminent Arrival' type is 2.
            BoardNote imminentArrivalNote{10, 2};

            REQUIRE_THROWS(spot.tagNote(imminentArrivalNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(1 == spot.getType());
        }

        SECTION("and a 'Departure' type, then the Spot's boxId and type will change to -1 and -1.")
        {
            // Box with boxId 10 leaves.
            // 'Departure' type is 3.
            BoardNote departureNote{10, 3};

            REQUIRE(true == spot.tagNote(departureNote));
            REQUIRE(-1 == spot.getBoxId());
            REQUIRE(-1 == spot.getType());
        }
        
        SECTION("and an 'Arrival' type, then an exception is thrown. The Spot's type must be 'Imminent Arrival' to accept an 'Arrival' note.")
        {
            // Box with boxId 10 arrives.
            // 'Arrival' type is 4.
            BoardNote arrivalNote{10, 4};

            REQUIRE_THROWS(spot.tagNote(arrivalNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(1 == spot.getType());
        }
    }


    SECTION("and receives a note with the with a different boxId")
        SECTION("and an 'Imminent Departure' type, then an exception is thrown. Spot's type must be 'Arrived' to accept an 'Imminent Departure' note.")
        {
            // Box with boxId 99 is about to leave.
            // 'Imminent Departure' type is 1.
            BoardNote imminentDepartureNote{99, 1};

            REQUIRE_THROWS(spot.tagNote(imminentDepartureNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(1 == spot.getType());
        }
        
        SECTION("and an 'Imminent Arrival' type, then false is returned, because the Spot currently has the original box, and two boxes can not be at the same spot.")
        {
            // Box with boxId 99 is about to arrive.
            // 'Imminent Arrival' type is 2.
            BoardNote imminentArrivalNote{99, 2};

            REQUIRE_FALSE(spot.tagNote(imminentArrivalNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(1 == spot.getType());
        }

        SECTION("and a 'Departure' type, then an exception is thrown. Spot's type must be 'ImminentDeparture' to accept an 'Departure' note.")
        {
            // Box with boxId 99 leaves.
            // 'Departure' type is 3.
            BoardNote departureNote{99, 3};

            REQUIRE_THROWS(spot.tagNote(departureNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(1 == spot.getType());
        }
        
        SECTION("and an 'Arrival' type, then an exception is thrown. Spot's type must be 'Imminent Arrival' to accept an 'Arrival' note.")
        {
            // Box with boxId 99 arrives.
            // 'Arrives' type is 4.
            BoardNote arrivalNote{99, 4};

            REQUIRE_THROWS(spot.tagNote(arrivalNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(1 == spot.getType());
        }
    }

TEST_CASE("Spot:: Spot originally has the type 'Imminent Arrival'")
{
    // Box with boxId 10 is about to arrive.
    // 'Imminent Arrival' type is 2.
    BoardNote imminentArrivalNote{10, 2};
    Spot spot{Position{100, 200}};
    spot.tagNote(imminentArrivalNote);

    SECTION("and receives a note with the same boxId")
    {
        SECTION("and 'Imminent Departure' type, then an exception is thrown. Spot's type must be 'Arrival' to accept an 'Imminent Departure' note.")
        {
            // Box with boxId 10 is about to leave.
            // 'Imminent Departure' type is 1.
            BoardNote imminentDepartureNote{10, 1};

            REQUIRE_THROWS(spot.tagNote(imminentDepartureNote));
            
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(2 == spot.getType());
        }
        
        SECTION("and 'Imminent Arrival' type, then an exception is thrown because the box is already about to leave.")
        {
            // Box with boxId 10 is about to arrive.
            // 'Imminent Arrival' type is 2.
            BoardNote imminentArrivalNote{10, 2};

            REQUIRE_THROWS(spot.tagNote(imminentArrivalNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(2 == spot.getType());
        }

        SECTION("and 'Departure' type, then an exception is thrown. Spot's type must be 'Imminent Departure' note to accept a 'Departure' note.")
        {
            // Box with boxId 10 leaves.
            // 'Departure' type is 3.
            BoardNote departureNote{10, 3};

            REQUIRE_THROWS(spot.tagNote(departureNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(2 == spot.getType());
        }
        
        SECTION("and 'Arrival' type, then Spot will have type 4.")
        {
            // Box with boxId 10 arrives.
            // 'Arrives' type is 4.
            BoardNote arrivalNote{10, 4};

            REQUIRE(true == spot.tagNote(arrivalNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(4 == spot.getType());
        }

    }
    
    SECTION("and receives a note with a different box (different boxId)")
    {
        SECTION("and 'ImminentDeparture' type, then an exception is thrown. Spot must receive an 'Arrival note before it can accept an 'Imminent Departure' note.")
        {
            // Box with boxId 99 is about to leave.
            // 'Imminent Departure' type is 1.
            BoardNote imminentDepartureNote{99, 1};

            REQUIRE_THROWS(spot.tagNote(imminentDepartureNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(2 == spot.getType());
        }
        
        SECTION("and 'Imminent Arrival' type, then false is returned. The Spot already contains a box.")
        {
            // Box with boxId 99 is about to arrive.
            // 'Imminent Arrival' type is 2.
            BoardNote imminentArrivalNote{99, 2};

            REQUIRE_FALSE(spot.tagNote(imminentArrivalNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(2 == spot.getType());
        }

        SECTION("and 'Departure' type, then an exception is thrown. Spot must receive an 'Imminent Departure' note before accepting a 'Departure' note.")
        {
            // Box with boxId 99 leaves.
            // 'Departure' type is 3.
            BoardNote departureNote{99, 3};

            REQUIRE_THROWS(spot.tagNote(departureNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(2 == spot.getType());
        }
        
        SECTION("and 'Arrival' type, then an exception is thrown. Spot must receive an 'Imminent Arrival' note with the same boxId before accepting an 'Arrival' note.")
        {
            // Box with boxId 99 arrives.
            // 'Arrives' type is 4.
            BoardNote arrivalNote{99, 4};

            REQUIRE_THROWS(spot.tagNote(arrivalNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(2 == spot.getType());
        }
    }
}

TEST_CASE("Spot:: Spot originally has the type 'Arrived'")
{
    // Box with boxId 10 has arrived.
    // 'Arrival' type is 4.
    BoardNote imminentArrivalNote{10, 2};
    BoardNote arrivalNote{10, 4};
    Spot spot{Position{100, 200}};
    spot.tagNote(imminentArrivalNote);
    spot.tagNote(arrivalNote);

    SECTION("and receives a note with the same boxId")
    {
        SECTION("and 'Imminent Departure' type, then the Spot's type will change to type 1.")
        {
            // Box with boxId 10 is about to leave.
            // 'Imminent Departure' type is 1.
            BoardNote imminentDepartureNote{10, 1};

            REQUIRE(true == spot.tagNote(imminentDepartureNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(1 == spot.getType());
        }
        
        SECTION("and 'Imminent Arrival' type, then an exception is thrown because the box can not be about to arrive, it has already arrived.")
        {
            // Box with boxId 10 is about to arrive.
            // 'Imminent Arrival' type is 2.
            BoardNote imminentArrivalNote{10, 2};

            REQUIRE_THROWS(spot.tagNote(imminentArrivalNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(4 == spot.getType());
        }

        SECTION("and 'Departure' type, then an exception is thrown. A Spot's type must be 'Imminent Departure' to accept a 'Departure' note.")
        {
            // Box with boxId 10 leaves.
            // 'Departure' type is 3.
            BoardNote departureNote{10, 3};

            REQUIRE_THROWS(spot.tagNote(departureNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(4 == spot.getType());
        }
        
        SECTION("and 'Arrival' type, then an exception is thrown. Spot's type must be 'Imminent Arrival' to accept an 'Arrival' note.")
        {
            // Box with boxId 10 arrives.
            // 'Arrival' type is 4.
            BoardNote arrivalNote{10, 4};

            REQUIRE_THROWS(spot.tagNote(arrivalNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(4 == spot.getType());
        }

    }

    SECTION("and receives a note with a different box (different boxId)")
    {
        SECTION("and 'Imminent Departure' type, then an exception is thrown. Spot's type  must be 'Arrival' to accept an 'Imminent Departure' note.")
        {
            // Box with boxId 99 is about to leave.
            // 'Imminent Departure' type is 1.
            BoardNote imminentDepartureNote{99, 1};

            REQUIRE_THROWS(spot.tagNote(imminentDepartureNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(4 == spot.getType());
        }

        SECTION("and 'Imminent Arrival' type, then false is returned. Two boxes can not be at the same spot.")
        {
            // Box with boxId 99 is about to arrive.
            // 'Imminent Arrival' type is 2.
            BoardNote imminentArrivalNote{99, 2};

            REQUIRE_FALSE(spot.tagNote(imminentArrivalNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(4 == spot.getType());
        }

        SECTION("and 'Departure' type, then an exception is thrown. Spot's type must be 'Imminent Departure' to accept a 'Departure' note.")
        {
            // Box with boxId 99 leaves.
            // 'Departure' type is 3.
            BoardNote departureNote{99, 3};

            REQUIRE_THROWS(spot.tagNote(departureNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(4 == spot.getType());
        }
        
        SECTION("and 'Arrival' type, then an exception is thrown. Spot's type  must be 'Imminent Arrival' to accept an 'Arrival' note.")
        {
            // boxId 99 arrives. "Arrives" type is 4.
            BoardNote arrivalNote{99, 4};

            REQUIRE_THROWS(spot.tagNote(arrivalNote));
            REQUIRE(10 == spot.getBoxId());
            REQUIRE(4 == spot.getType());
        }

    }
}


