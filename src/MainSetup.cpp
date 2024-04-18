#include "MainSetup.h"

using namespace std;

void MainSetup::addGroupsOfBoxes(
    vector<Box>& boxes,
    int firstBoxId,
    int firstGroupNum,
    int numOfGroups,
    int groupSize)
{
    for(int gn = firstGroupNum; gn<numOfGroups+firstGroupNum; ++gn)
    {
        int temp = firstBoxId + (groupSize * gn);
        for(int ii=0; ii<groupSize; ++ii)
        {
            boxes.push_back(Box{temp+ii, gn, 3, 3});
        }
    }
}
void MainSetup::addAGroupOfBoxes(
    vector<Box>& boxes,
    int firstBoxId,
    int groupId,
    int groupSize)
{
    for(int ii=0; ii<groupSize; ++ii)
    {
        boxes.push_back(Box{firstBoxId+ii, groupId, 3, 3});
    }
}


/* Placement of entrances and exits to plaza

                North Wall
              -----    ------
            --------------------
           |                    |  
          ||                    ||
          ||                    ||
          ||                    ||
West Wall  |                    |  East Wall
          ||                    ||
          ||                    ||
          ||                    ||
           |                    |
            --------------------
               ______   ______
                  South Wall
*/

vector<pair<Position, Position>> MainSetup::getEndRectangles(int bW, int bH)
{
    vector<pair<Position, Position>> endRanges{};
    endRanges.push_back({Position{bW/2-50, 0},   Position{bW/2+50, 10}});         // North wall at center
    endRanges.push_back({Position{0, bW/4-25},   Position{10, bW/4+25}});         // West wall at top 
    endRanges.push_back({Position{bW-11, bH/4-25}, Position{bW-1, bH/4+25}});     // East wall at top 
    endRanges.push_back({Position{0, bW*3/4-25},   Position{10, bW*3/4+25}});     // West wall at bottom 
    endRanges.push_back({Position{bW-11, bH*3/4-25}, Position{bW-1, bH*3/4+25}}); // East wall at bottom 
    endRanges.push_back({Position{bW*3/4-25, bH-11}, Position{bW*3/4+25, bH-1}}); // South wall at left
    endRanges.push_back({Position{bW/4-25, bH-11}, Position{bW/4+25, bH-1}});     // South wall at right 
    return endRanges;
}

vector<pair<Position, Position>> MainSetup::deleteRect(
    vector<pair<Position, Position>> rectangles,
    pair<Position, Position> rectangle)
{
    vector<pair<Position, Position>> reduced{};
    for(pair<Position, Position> rect : rectangles)
    {
        if(!(rect == rectangle))
        {
            reduced.push_back(rect);
        }
    }
    return reduced;
}
