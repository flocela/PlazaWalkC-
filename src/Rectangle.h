#ifndef RECKTANGLE__H
#define RECKTANGLE__H


#include "Position.h"


class Rectangle
{
    public:
    
    Rectangle(Position a, Position b);
    
    Position getTopLeft() const;
    Position getBottomRight() const;

    // TODO test
    bool operator== (const Rectangle& o) const;


    private:

    Position _topLeft;
    Position _bottomRight;   
};


#endif

