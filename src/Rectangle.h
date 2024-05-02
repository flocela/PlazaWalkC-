#ifndef RECKTANGLE__H
#define RECKTANGLE__H


#include "Position.h"


class Rectangle
{
    public:
    
    Rectangle(Position a, Position b);
    
    Position getTopLeft() const;
    Position getBottomRight() const;
    Position getCenter() const;
    bool isInside(Position p) const;

    std::string toString() const;

    // TODO test
    bool operator== (const Rectangle& o) const;

    // TODO needs test. 
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

