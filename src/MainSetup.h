#ifndef MAINSETUP__H
#define MAINSETUP__H

#include <vector>

#include "Box.h"
#include "Color.h"
#include "Position.h"
#include "Rectangle.h"

class MainSetup
{

    public:

    /*
    Appends one group of Boxes to @boxes.
    The first appended box has a boxId of @firstBoxId and a groupId of @groupId.
    The size of the group is @groupSize. 
    */
    static void addAGroupOfBoxes(
        std::vector<Box>& boxes,
        int firstBoxId,
        int groupId,
        int groupSize);
  
    /* 
    Returns a predefined vector of Rectangles. 
    */
    static std::vector<Rectangle> getInOutBoundRectangles(
        int boardWidth,
        int boardHeight);
  
    /* 
    Deletes the one Rectangle @rectangle from @rectangles.
    */
    static std::vector<Rectangle> deleteRect(
                std::vector<Rectangle> rectangles,
                Rectangle discardR);
   
    /*
    Predefined vector<vector<uint8_t>> which can be used to make Colors.
    */ 
    static Color red();
    static Color cyan();
    static Color amber();
    static Color purple();
};

#endif
