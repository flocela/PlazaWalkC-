#include "MainSetup.h"

using namespace std;

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
                  ------
            --------------------
           |                    |  
          ||                    ||
          ||                    ||
          ||                    ||
West Walls |                    |  East Walls
          ||                    ||
          ||                    ||
          ||                    ||
           |                    |
            --------------------
               ______   ______
                  South Walls
*/

vector<Rectangle> MainSetup::getInOutBoundRectangles(int bW, int bH)
{
    vector<Rectangle> inOut{};
    inOut.push_back(Rectangle{Position{bW/2-50, 0},       Position{bW/2+50, 10}});     // North wall at center
    inOut.push_back(Rectangle{Position{0, bW/4-25},       Position{10, bW/4+25}});     // West wall at top 
    inOut.push_back(Rectangle{Position{bW-11, bH/4-25},   Position{bW-1, bH/4+25}});   // East wall at top 
    inOut.push_back(Rectangle{Position{0, bW*3/4-25},     Position{10, bW*3/4+25}});   // West wall at bottom 
    inOut.push_back(Rectangle{Position{bW-11, bH*3/4-25}, Position{bW-1, bH*3/4+25}}); // East wall at bottom
    inOut.push_back(Rectangle{Position{bW*3/4-25, bH-11}, Position{bW*3/4+25, bH-1}}); // South wall at left
    inOut.push_back(Rectangle{Position{bW/4-25, bH-11},   Position{bW/4+25, bH-1}});   // South wall at right 

    return inOut;
}

vector<Rectangle> MainSetup::deleteRect(
    vector<Rectangle> rectangles,
    Rectangle discardR)
{
    vector<Rectangle> reduced{};
    for(const Rectangle& rect : rectangles)
    {
        if(!(rect == discardR))
        {
            reduced.push_back(rect);
        }
    }
    return reduced;
}

vector<vector<uint8_t>> MainSetup::red()
{
    return vector<vector<uint8_t>>{
    // {0xFF, 0xEB, 0xEE},
    {0xFF, 0xCD, 0xD2},
    {0xEF, 0x9A, 0x9A},
    {0xE5, 0x73, 0x73},
    {0xEF, 0x53, 0x50},
    {0xF4, 0x43, 0x36},
    {0xE5, 0x39, 0x35},
    {0xD3, 0x2F, 0x2F},
    {0xC6, 0x28, 0x28},
    {0xB7, 0x1C, 0x1C}
    };
}

vector<vector<uint8_t>> MainSetup::cyan()
{
    return vector<vector<uint8_t>> {
    //{0xE0, 0xF7, 0xFA},
    {0xB2, 0xEB, 0xF2},
    {0x80, 0xDE, 0xEA},
    {0x4D, 0xD0, 0xE1},
    {0x26, 0xC6, 0xDA},
    {0x00, 0xBC, 0xD4},
    {0x00, 0xAC, 0xC1},
    {0x00, 0x97, 0xA7},
    {0x00, 0x83, 0x8F},
    {0x00, 0x60, 0x64},
    };
}

vector<vector<uint8_t>> MainSetup::amber()
{
    return vector<vector<uint8_t>> {
    //{0xFF, 0xF8, 0xE1},
    {0xFF, 0xEC, 0xB3},
    {0xFF, 0xE0, 0x82},
    {0xFF, 0xD5, 0x4F},
    {0xFF, 0xCA, 0x28},
    {0xFF, 0xC1, 0x07},
    {0xFF, 0xB3, 0x00},
    {0xFF, 0xA0, 0x00},
    {0xFF, 0x8F, 0x00},
    {0xFF, 0x6F, 0x00},
    };
}

vector<vector<uint8_t>> MainSetup::purple()
{
    return vector<vector<uint8_t>> {
    //{0xF3, 0xE5, 0xF5},
    {0xE1, 0xBE, 0xE7},
    {0xCE, 0x93, 0xD8},
    {0xBA, 0x68, 0xC8},
    {0xAB, 0x47, 0xBC},
    {0x9C, 0x27, 0xB0},
    {0x8E, 0x24, 0xAA},
    {0x7B, 0x1F, 0xA2},
    {0x6A, 0x1B, 0x9A},
    {0x4A, 0x14, 0x8C},
    };
}


