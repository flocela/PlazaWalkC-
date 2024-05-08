#ifndef RECKTANGLE__H
#define RECKTANGLE__H


#include "Position.h"


class Rectangle
{
    public:
   
    /*
    @topLeft is the top left corner of the Rectangle.
    @bottomRight is the bottom right corner of the Rectangle.
    */ 
    Rectangle(Position topLeft, Position bottomRight);
    
    Position getTopLeft() const;
    Position getBottomRight() const;
    Position getCenter() const;

    /*
    Returns true if @p is inside the Rectangle. To be inside, 1) @p's x value must be equal to or greater than the top left corner's x value and must be equal to or smaller than the bottom right corner's x value, 2) @p's y value must be equal to or greater than the top left corner's y value and must be equal to or smaller than the bottom right corner's y value.
    */
    bool isInside(Position p) const;

    std::string toString() const;

    bool operator== (const Rectangle& o) const;

    /*
    Returns the top left and bottom right corners of a Rectangle. A Rectangle of width 10 and height 11, may print out as "{1, 1}, {11, 12}"
    */
    friend std::ostream& operator<< (std::ostream& o, const Rectangle& r)
    {
        o << "[" << r._topLeft << ", " << r._bottomRight << 
             "]";
        return o;
    }


    private:

    Position _topLeft;
    Position _bottomRight;   
};


#endif

