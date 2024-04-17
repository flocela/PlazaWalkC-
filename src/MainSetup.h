#ifndef MAINSETUP__H
#define MAINSETUP__H

#include <vector>

#include "Box.h"
#include "Position.h"

class MainSetup
{
public:
    
    static void addGroupsOfBoxes(
        std::vector<Box>& boxes,
        int firstBoxId,
        int firstGroupNum,
        int numOfGroups,
        int groupSize);
    
    static void addAGroupOfBoxes(
        std::vector<Box>& boxes,
        int firstBoxId,
        int groupId,
        int groupSize);
    
    static std::vector<std::pair<Position, Position>> getEndRectangles(
        int boardWidth,
        int boardHeight);
    
    static std::vector<std::pair<Position, Position>> deleteRect(
                std::vector<std::pair<Position, Position>> rectangles,
                std::pair<Position, Position> rectangle);
};

#endif
