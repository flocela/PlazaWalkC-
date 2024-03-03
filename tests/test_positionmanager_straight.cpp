#include "catch.hpp"
#include "../src/PositionManager_Straight.h"

using namespace std;

TEST_CASE("atEnd() return false if position is outside ending box")
{
    PositionManager_Straight pm{
        Position{70, 50},
        Position{75, 80},
        0,
        99,
        0,
        99};

    REQUIRE(false == pm.atEnd(Position{69, 70}));
}

TEST_CASE("atEnd() return false if position is inside ending box")
{
    PositionManager_Straight pm{
        Position{70, 50},
        Position{75, 80},
        0,
        99,
        0,
        99};

    REQUIRE(pm.atEnd(Position{70, 50}));
    REQUIRE(pm.atEnd(Position{72, 70}));
    REQUIRE(pm.atEnd(Position{72, 80}));
}

TEST_CASE("target is east of box")
{
    PositionManager_Straight pm{
        Position{50, 50},
        Position{55, 70},
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

TEST_CASE("target is southeast of box")
{
    PositionManager_Straight pm{
        Position{50, 50},
        Position{55, 70},
        0,
        99,
        0,
        99};
    
    Position position{0, 0};
    while (!pm.atEnd(position))
    {
        vector<Position> futurePositions = pm.getFuturePositions(position);
        Position newPosition = futurePositions[0];
        int nX = newPosition.getX();
        int nY = newPosition.getY();
        int pX = position.getX();
        int pY = position.getY();
        REQUIRE( ( ( (nX == (pX+1)) && (nY == pY)     ) ||
                   ( (nX == pX)      && (nY == (pY+1)) )
                 )
        );
        position = newPosition;
     } 
}

TEST_CASE("target is south of box")
{
    PositionManager_Straight pm{
        Position{50, 50},
        Position{55, 70},
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

TEST_CASE("target is southwest of box")
{
    PositionManager_Straight pm{
        Position{50, 50},
        Position{55, 70},
        0,
        99,
        0,
        99};
    
    Position position{99, 0};
    while (!pm.atEnd(position))
    {
        vector<Position> futurePositions = pm.getFuturePositions(position);
        Position newPosition = futurePositions[0];
        int nX = newPosition.getX();
        int nY = newPosition.getY();
        int pX = position.getX();
        int pY = position.getY();
        REQUIRE( ( ( (nX == (pX-1)) && (nY == pY)     ) ||
                   ( (nX == pX)      && (nY == (pY+1)) )
                 )
        );
        position = newPosition;
     }
}

TEST_CASE("target is west of box")
{
    PositionManager_Straight pm{
        Position{50, 50},
        Position{55, 70},
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

TEST_CASE("target is northwest of box")
{
    PositionManager_Straight pm{
        Position{50, 50},
        Position{55, 70},
        0,
        99,
        0,
        99};
    
    Position position{99, 99};
    while (!pm.atEnd(position))
    {
        vector<Position> futurePositions = pm.getFuturePositions(position);
        Position newPosition = futurePositions[0];
        int nX = newPosition.getX();
        int nY = newPosition.getY();
        int pX = position.getX();
        int pY = position.getY();
        REQUIRE( ( ( (nX == (pX-1)) && (nY == pY)     ) ||
                   ( (nX == pX)      && (nY == (pY-1)) )
                 )
        );
        position = newPosition;
     }
}

TEST_CASE("target is north of box")
{
    PositionManager_Straight pm{
        Position{50, 50},
        Position{55, 70},
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

TEST_CASE("target is northeast of box")
{
    PositionManager_Straight pm{
        Position{50, 50},
        Position{55, 70},
        0,
        99,
        0,
        99};
    
    Position position{0, 99};
    while (!pm.atEnd(position))
    {
        vector<Position> futurePositions = pm.getFuturePositions(position);
        Position newPosition = futurePositions[0];
        int nX = newPosition.getX();
        int nY = newPosition.getY();
        int pX = position.getX();
        int pY = position.getY();
        REQUIRE( ( ( (nX == (pX+1)) && (nY == pY)     ) ||
                   ( (nX == pX)      && (nY == (pY-1)) )
                 )
        );
        position = newPosition;
     }
}
