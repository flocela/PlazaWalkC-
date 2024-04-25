#include "Printer.h"
#include <iostream>

using namespace std;


Printer::Printer(SDL_Renderer* renderer): _renderer{renderer} {}

// TODO there should be a unique_locck here so one print job finishes before the next one starts.
void Printer::receiveAllDropsAllBoxes(unordered_set<Drop> drops, unordered_map<int, BoxInfo> boxes) 
{
    print(drops, boxes);
}

void Printer::print(unordered_set<Drop> drops, unordered_map<int, BoxInfo> boxes)
{  (void)drops;
    (void)boxes;
    (void)_renderer;

    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    // Every group number has a Color in _colorPerGroupNumber.
    // _dropsPerShadePerGroupNumber has a vector for every group number. That vector has an index for every shade that Color has. Drops are put into the index corresponding to their shade. If a Drop's level is equal to or larger than the number of shades, then Drop is placed in the last shade.
    unordered_map<int, vector<vector<Drop>>> dropsPerShadePerGroupNumber;
    for(auto& groupNumberAndColor : _colorPerGroupNumber)
    {
        int groupNum = groupNumberAndColor.first;
        dropsPerShadePerGroupNumber.insert({groupNum, vector<vector<Drop>>(_numOfShadesPerGroupNumber[groupNum])});
    }
    for (const Drop& drop: drops)
    {
        int id = drop.getBoxId();
        int groupId = boxes.at(id).getGroupId();
        int level = boxes.at(id).getLevel();
        if (level >= _colorPerGroupNumber.at(groupId).getNumberOfShades())
        {
            dropsPerShadePerGroupNumber.at(groupId).at(_numOfShadesPerGroupNumber.at(groupId)-1).push_back(drop);
        }
        else
        {
            dropsPerShadePerGroupNumber.at(groupId).at(level).push_back(drop);
        }
    }

    for(auto& groupNumberAndDropsPerShade : dropsPerShadePerGroupNumber)
    {
        int groupNumber = groupNumberAndDropsPerShade.first;
        vector<vector<Drop>>& vectorOfDropsPerShade = groupNumberAndDropsPerShade.second;
        for(size_t ii=0; ii<vectorOfDropsPerShade.size(); ++ii)
        {
            Color& color = _colorPerGroupNumber.at(groupNumber);
            for(Drop& drop : vectorOfDropsPerShade[ii])
            {
                SDL_Rect squareRect;
                squareRect.w = 3;// TODO width and height is taken from box width and height not hardcoded
                squareRect.h = 3;
                squareRect.x = drop.getPosition().getX();
                squareRect.y = drop.getPosition().getY();
                SDL_SetRenderDrawColor(_renderer, color.getRed(ii), color.getGreen(ii), color.getBlue(ii), 0xFF);
                SDL_RenderFillRect(_renderer, &squareRect);
            }
        }
    }

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
        
