#include "MainSetup.h"

using namespace std;

vector<Box> MainSetup::getBoxes(int firstBoxId, int numOfGroups, int groupSize)
{
    vector<Box> boxes{};
    for(int groupNum=0; groupNum<numOfGroups; ++groupNum)
    {
        int boxId = firstBoxId + (groupSize * groupNum);
        for(int boxIdx=0; boxIdx<groupSize; ++boxIdx)
        {
            boxes.push_back(Box{boxId+boxIdx, groupNum, 3, 3});
        }
    }
    return boxes;
}

vector<pair<Position, Position>> MainSetup::getEndRectangles()
{
    vector<pair<Position, Position>> endRanges{};
    endRanges.push_back({Position{350, 0},   Position{450, 10}}); 
    endRanges.push_back({Position{789, 175}, Position{799, 225}}); 
    endRanges.push_back({Position{789, 575}, Position{799, 625}});
    endRanges.push_back({Position{575, 789}, Position{625, 799}});
    endRanges.push_back({Position{175, 789}, Position{225, 799}});
    endRanges.push_back({Position{0, 575},   Position{10, 625}});
    endRanges.push_back({Position{0, 175},   Position{10, 225}});
    return endRanges;
}
