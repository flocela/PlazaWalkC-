#ifndef MAINSETUP__H
#define MAINSETUP__H

#include <vector>

#include "Box.h"
#include "Position.h"

class MainSetup
{
public:

    // Appends numOfGroups of Boxes to boxes.
    // The first appended box has a boxId of firtBoxId and a group number of firstGroupNumber.
    // Each group is of size groupSize.
    // Each new box's id goes up by one.
    // The group number of each group goes up by one also.    
    static void addGroupsOfBoxes(
        std::vector<Box>& boxes,
        int firstBoxId,
        int firstGroupNum,
        int numOfGroups,
        int groupSize);
   
    // Appends one group of boxes to boxes.
    // The first appended box has a boxId of firstBoxId and groupId of groupId.
    // The size of the group is groupSize. 
    static void addAGroupOfBoxes(
        std::vector<Box>& boxes,
        int firstBoxId,
        int groupId,
        int groupSize);
   
    // Returns a predefined vector of rectangles. Each rectangle is a pair of Positions, where the first position is the top left corner of the rectangle and the second Position is the bottom right corner of the rectangle.
    static std::vector<std::pair<Position, Position>> getEndRectangles(
        int boardWidth,
        int boardHeight);
   
    // Deletes one rectangle (which is a pair of Positions) from rectangles. Rectangles are made up of two Positions, first being the top left corner, the second being the bottom right corner. 
    static std::vector<std::pair<Position, Position>> deleteRect(
                std::vector<std::pair<Position, Position>> rectangles,
                std::pair<Position, Position> rectangle);
    
    static std::vector<std::vector<uint8_t>> red();
    static std::vector<std::vector<uint8_t>> cyan();
    static std::vector<std::vector<uint8_t>> amber();
    static std::vector<std::vector<uint8_t>> purple();
};

#endif
