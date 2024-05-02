#include "catch.hpp"
#include "../src/PositionManager_Diagonal.h"

using namespace std;

TEST_CASE("PositionManager_Diagonal_core::")
{
    SECTION("In constructor, passing a target Position that is outside of the end Rectangle results in an exception.")
    {
        REQUIRE_THROWS(PositionManager_Diagonal{
            Rectangle{Position{70, 50},Position{75, 80}},
            Position{69, 50},
            0,
            99,
            0,
            99});
    }
        
    SECTION("In constructor, passing a targetPosition that is on the edge of endRectangle does not result in an exception. The allowable ranges from endRectangle for the targetPosition are inclusive.")
    {
        REQUIRE_NOTHROW(PositionManager_Diagonal{
            Rectangle{Position{70, 50},Position{75, 80}},
            Position{70,50},
            0,
            99,
            0,
            99});
    }

    SECTION("atEnd() return false if Position is outside end Rectangle")
    {
        PositionManager_Diagonal pm{
            Rectangle{Position{70, 50},Position{75, 80}},
            Position{72, 65},
            0,
            99,
            0,
            99};

        REQUIRE(false == pm.atEnd(Position{69, 70}));
    }

    SECTION("atEnd() return true if position is inside ending box")
    {
        PositionManager_Diagonal pm{
            Rectangle{Position{70, 50}, Position{75, 80}},
            Position{72, 65},
            0,
            99,
            0,
            99};

        REQUIRE(pm.atEnd(Position{70, 50}));
        REQUIRE(pm.atEnd(Position{72, 70}));
        REQUIRE(pm.atEnd(Position{72, 80}));
    }

    SECTION("target Position is east of box")
    {
        PositionManager_Diagonal pm{
            Rectangle{Position{50, 50}, Position{55, 70}},
            Position{52, 60},
            0,
            99,
            0,
            99};
        
        Position position{0, 60};
        while (!pm.atEnd(position))
        {
            vector<Position> futurePositions = pm.getFuturePositions(position);
            Position newPosition = futurePositions[0];
            REQUIRE(newPosition.getX() == position.getX() + 1);
            REQUIRE(newPosition.getY() == position.getY());
            
            position = newPosition;
        }
    }

    SECTION("target Position is southeast of box")
    {
        PositionManager_Diagonal pm{
            Rectangle{Position{50, 70}, Position{55, 80}},
            Position{52, 75},
            0,
            99,
            0,
            99};
        
        Position position{0, 0};
        int ii = 0;
        int diagonalMovesCount = 0;
        while (!pm.atEnd(position))
        {
            vector<Position> futurePositions = pm.getFuturePositions(position);
            Position newPosition = futurePositions[0];
            int nX = newPosition.getX();
            int nY = newPosition.getY();
            int pX = position.getX();
            int pY = position.getY();
            
            if (ii<=52)
            {
                REQUIRE( (nX = pX+1 && nY == pY+1) );
            }
            else
            {
                
                REQUIRE(( (nX == pX) && (nY == (pY+1)) ));
            }
            position = newPosition;
            ++ii;
         }
         REQUIRE(70 == ii);
    }

    SECTION("target Position is south of box")
    {
        PositionManager_Diagonal pm{
            Rectangle{Position{50, 50}, Position{55, 70}},
            Position{52, 60},
            0,
            99,
            0,
            99};
        
        Position position{52, 0};
        while (!pm.atEnd(position))
        {
            vector<Position> futurePositions = pm.getFuturePositions(position);
            Position newPosition = futurePositions[0];
            int nX = newPosition.getX();
            int nY = newPosition.getY();
            int pX = position.getX();
            int pY = position.getY();
            REQUIRE( ((nX == pX) && (nY == (pY+1)) )
            );
            position = newPosition;
         } 
    }

    SECTION("target Position is southwest of box")
    {
        PositionManager_Diagonal pm{
            Rectangle{Position{50, 70}, Position{55, 80}},
            Position{52, 75},
            0,
            99,
            0,
            99};
        
        Position position{99, 0};
        int ii = 0;
        int diagonalMovesCount = 0;
        while (!pm.atEnd(position))
        {
            vector<Position> futurePositions = pm.getFuturePositions(position);
            Position newPosition = futurePositions[0];
            int nX = newPosition.getX();
            int nY = newPosition.getY();
            int pX = position.getX();
            int pY = position.getY();
            if (ii<=52)
            {
                REQUIRE( (nX = pX-1 && nY == pY+1) );
            }
            else
            {
                REQUIRE(( (nX == pX) && (nY == (pY+1)) ));
            }
            position = newPosition;
            ++ii;
         }
         REQUIRE(70 == ii);
    }

    SECTION("target Position is west of box")
    {
        PositionManager_Diagonal pm{
            Rectangle{Position{20, 50}, Position{30, 70}},
            Position{25, 60},
            0,
            99,
            0,
            99};
        
        Position position{99, 60};
        while (!pm.atEnd(position))
        {
            vector<Position> futurePositions = pm.getFuturePositions(position);
            Position newPosition = futurePositions[0];
            REQUIRE(newPosition.getX() == position.getX() - 1);
            REQUIRE(newPosition.getY() == position.getY());
            
            position = newPosition;
        }
    }

    SECTION("target Position is northwest of box")
    {
        PositionManager_Diagonal pm{
            Rectangle{Position{20, 70}, Position{30, 80}},
            Position{25, 75},
            0,
            99,
            0,
            99};
        
        int ii = 0;
        Position position{99, 99};
        while (!pm.atEnd(position))
        {
            vector<Position> futurePositions = pm.getFuturePositions(position);
            Position newPosition = futurePositions[0];
            int nX = newPosition.getX();
            int nY = newPosition.getY();
            int pX = position.getX();
            int pY = position.getY();
            if (ii<=23)
            {
                REQUIRE( (nX = pX-1 && nY == pY-1) );
            }
            else
            {
                REQUIRE(( (nX == (pX-1)) && (nY == pY) ));
            }
            position = newPosition;
            ++ii;
         }

         REQUIRE(69 == ii);
    }

    SECTION("target Position is north of box")
    {
        PositionManager_Diagonal pm{
            Rectangle{Position{50, 50}, Position{55, 70}},
            Position{52, 60},
            0,
            99,
            0,
            99};
        
        Position position{52, 99};
        while (!pm.atEnd(position))
        {
            vector<Position> futurePositions = pm.getFuturePositions(position);
            Position newPosition = futurePositions[0];
            int nX = newPosition.getX();
            int nY = newPosition.getY();
            int pX = position.getX();
            int pY = position.getY();
            REQUIRE( ((nX == pX) && (nY == (pY-1)) )
            );
            position = newPosition;
         }
    }

    SECTION("target Position is northeast of box")
    {
        PositionManager_Diagonal pm{
            Rectangle{Position{70, 50}, Position{80, 55}},
            Position{75, 52},
            0,
            99,
            0,
            99};
        
        int ii = 0;
        Position position{0, 99};
        while (!pm.atEnd(position))
        {
            vector<Position> futurePositions = pm.getFuturePositions(position);
            Position newPosition = futurePositions[0];
            int nX = newPosition.getX();
            int nY = newPosition.getY();
            int pX = position.getX();
            int pY = position.getY();
            if (ii<=46)
            {
                REQUIRE( (nX = pX+1 && nY == pY-1) );
            }
            else
            {
                REQUIRE(( (nX == (pX+1)) && (nY == pY) ));
            }
            position = newPosition;
            ++ii;
         }
         REQUIRE( 70 == ii);
    }

    SECTION("getEndRect() returns end rectangle that was given in the constructor.")
    {
        PositionManager_Diagonal pm{
            Rectangle{Position{70, 50}, Position{80, 55}},
            Position{71, 51},
            0,
            99,
            0,
            99};
        REQUIRE(Rectangle{Position{70, 50}, Position{80, 55}} == pm.getEndRect());
    }
        
    SECTION("getTargetRect() returns the center of the target rectangle that was given in the constructor.")
    {
        PositionManager_Diagonal pm{
            Rectangle{Position{70, 50}, Position{80, 55}},
            Position{71, 51},
            0,
            99,
            0,
            99};
        REQUIRE(Rectangle{Position{71, 51}, Position{71, 51}} == pm.getTargetRect());
    }
}

