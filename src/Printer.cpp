#include "Printer.h"
#include <iostream>
#include <map>
using namespace std;


Printer::Printer(SDL_Renderer* renderer): _renderer{renderer} {}

void Printer::receiveAllDropsAllBoxes(unordered_set<Drop> drops, unordered_map<int, BoxInfo> boxes) 
{
    print(drops, boxes);
}

void Printer::print(unordered_set<Drop> drops, unordered_map<int, BoxInfo> boxes)
{  

    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    // Print Boxes

    // Need to group the Drops by a union of their Color and shade. Color is taken from the Drop's group number. Shade is taken from the Drop's level.
    map<pair<int, int>, unordered_set<Drop>> dropsPerGroupNumberAndShade;

    for(auto& colorPerGroupNumber: _colorPerGroupNumber)
    {
        int groupNum = colorPerGroupNumber.first;
        int numOfShades = _numOfShadesPerGroupNumber[groupNum];

        for(int ii=0; ii<numOfShades; ++ii)
        {
            dropsPerGroupNumberAndShade[{groupNum, ii}] = unordered_set<Drop>{};
        }
    }

    for (const Drop& drop: drops)
    {
        int id = drop.getBoxId();
        int level = boxes.at(id).getLevel();
        int groupId = boxes.at(id).getGroupId();
    
        // If the level is greater or equal to the number of shades, then set the shade to the last shade.
        int numOfShades = _colorPerGroupNumber.at(groupId).getNumberOfShades();
        int shade = (level >= numOfShades) ? (numOfShades-1) : (level);

        dropsPerGroupNumberAndShade[{groupId, shade}].insert(drop);
    }

    for(auto it=dropsPerGroupNumberAndShade.begin(); it!=dropsPerGroupNumberAndShade.end(); it++)
    {
        pair<int, int> groupIdAndShade = it->first;
        Color color = _colorPerGroupNumber.at(groupIdAndShade.first);
        int shade = groupIdAndShade.second;
        unordered_set<Drop>& drops = it->second;
        for(const Drop& drop : drops)
        {
            SDL_Rect squareRect;
            squareRect.w = 3;// TODO width and height is taken from box width and height not hardcoded
            squareRect.h = 3;
            squareRect.x = drop.getPosition().getX();
            squareRect.y = drop.getPosition().getY();
            SDL_SetRenderDrawColor(_renderer, color.getRed(shade), color.getGreen(shade), color.getBlue(shade), 0xFF);
            SDL_RenderFillRect(_renderer, &squareRect);
        }
        
    }

    // Print End Rectangles

    for(const pair<Position, Position>& endPoint : _endRectangles)
    {
        Position topLeft = endPoint.first;
        Position bottomRight = endPoint.second;
        
        SDL_Rect endRect;
        endRect.x = topLeft.getX();
        endRect.y = topLeft.getY();
        endRect.w = bottomRight.getX() - topLeft.getX();
        endRect.h = bottomRight.getY() - topLeft.getY();
        SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0x30);
        SDL_RenderFillRect(_renderer, &endRect);
    }

    SDL_RenderPresent(_renderer);

}

void Printer::addInOutBoundRectangle(Position topLeft, Position bottomRight)
{
    _endRectangles.push_back({topLeft, bottomRight});
}

void Printer::addInOutBoundRectangles(vector<pair<Position, Position>> rectangles)
{
    for(const auto& rect : rectangles)
    {
        _endRectangles.push_back(rect);
    }
}

void Printer::setGroupColors(std::unordered_map<int, Color> colorPerGroupNumber)
{
    _colorPerGroupNumber.clear();
    _numOfShadesPerGroupNumber.clear();
    for(auto& groupNumberAndColor : colorPerGroupNumber)
    {
        Color c = groupNumberAndColor.second;
        _numOfShadesPerGroupNumber.insert({groupNumberAndColor.first, c.getNumberOfShades()});
        _colorPerGroupNumber.insert({groupNumberAndColor.first, groupNumberAndColor.second});
    }
}
        
