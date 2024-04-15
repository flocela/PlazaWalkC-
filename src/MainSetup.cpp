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

vector<pair<Position, Position>> MainSetup::getEndRectangles(int bW, int bH)
{
    vector<pair<Position, Position>> endRanges{};
    endRanges.push_back({Position{bW/2-50, 0},   Position{bW/2+50, 10}}); 
    endRanges.push_back({Position{bW-11, bH/4-25}, Position{bW-1, bH/4+25}}); 
    endRanges.push_back({Position{bW-11, bH*3/4-25}, Position{bW-1, bH*3/4+25}});
    endRanges.push_back({Position{bW*3/4-25, bH-11}, Position{bW*3/4+25, bH-1}});
    endRanges.push_back({Position{bW/4-25, bH-11}, Position{bW/4+25, bH-1}});
    endRanges.push_back({Position{0, bW*3/4-25},   Position{10, bW*3/4+25}});
    endRanges.push_back({Position{0, bW/4-25},   Position{10, bW/4+25}});
    return endRanges;
}
