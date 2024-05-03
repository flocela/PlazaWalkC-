#include "catch.hpp"
#include "../src/Rectangle.h"

#include <sstream>

using namespace std;

TEST_CASE("Rectangle::core")
{

    SECTION("Bottom left corner and top right corner make a Rectangle.")
    {
        Rectangle rect{Position{100, 100}, Position{200, 50}};
        REQUIRE(Position{100, 50} == rect.getTopLeft());
        REQUIRE(Position{200, 100} == rect.getBottomRight());
    }

    SECTION("Top left corner and bottom right corner make a Rectangle.")
    {   
        Rectangle rect{Position{100, 50}, Position{100, 100}};
        REQUIRE(Position{100, 50} == rect.getTopLeft());
        REQUIRE(Position{100, 100} == rect.getBottomRight());
    }

    SECTION("toString() method shows the x and y values for the top left and bottom right corners.")
    {
        Rectangle rect{Position{1, 2}, {5, 6}};
        REQUIRE("[{1, 2}, {5, 6}]" == rect.toString());
    }

    SECTION("ostream operator  method shows the x and y values for the top left and bottom right corners.")
    {
        Rectangle rect{Position{1, 2}, Position{5, 6}};
        stringstream ss;
        ss << rect; 
        REQUIRE("[{1, 2}, {5, 6}]" == ss.str());
    }

    SECTION("Two Rectangles with the same Positions are equal.")
    {
        Rectangle rA{Position{1, 2}, Position{5, 6}};
        Rectangle rB{Position{5, 6}, Position{1, 2}};

        REQUIRE(rA == rB);
    }

    SECTION("Two Rectangles that do not have the same Positions are not equal.")
    {
        Rectangle rA{Position{1, 2}, Position{5, 6}};

        // Change x value of one of rB's top left corner.
        Rectangle rB{Position{5, 6}, Position{3, 2}};

        // Change y value of rB's top left corner.
        Rectangle rC{Position{1, 3}, Position{5, 6}};

        REQUIRE_FALSE(rA == rB);
        REQUIRE_FALSE(rA == rC);
    }

    SECTION("getCenter() returns the center of the Rectangle. Simple Case.")
    {
        Rectangle rect{Position{1, 2}, Position{5, 6}};

        REQUIRE(Position{3, 4} == rect.getCenter());
    }
    
    SECTION("getCenter() returns the center of the Rectangle. Rectangle has a width of zero.")
    {
        Rectangle rect{Position{1, 2}, Position{1, 6}};

        REQUIRE(Position{1, 4} == rect.getCenter());
    }

    SECTION("getCenter() returns the center of the Rectangle. Rectangle has a height of zero.")
    {
        Rectangle rect{Position{1, 6}, Position{5, 6}};

        REQUIRE(Position{3, 6} == rect.getCenter());
    }

    SECTION("isInside() returns true if @position is inside Rectangle.")
    {
        Rectangle rect{Position{1, 2}, Position{5, 6}};
        REQUIRE(rect.isInside(Position{2, 4}));
    }
        
    SECTION("isInside() returns true if @position is at vertical edge of Rectangle.")
    {
        Rectangle rect{Position{1, 2}, Position{5, 6}};
        REQUIRE(rect.isInside(Position{5, 4}));
    }
        
    SECTION("isInside() returns true if @position is at horizontal edge of Rectangle.")
    {
        Rectangle rect{Position{1, 2}, Position{5, 6}};
        REQUIRE(rect.isInside(Position{2, 2}));
    }
        
}

