#include "Printer.h"
#include <iostream>

using namespace std;


vector<vector<Uint8>> red{
//{0xFF, 0xEB, 0xEE},
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

vector<vector<Uint8>> cyan{
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

vector<vector<Uint8>> amber{
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

vector<vector<Uint8>> purple{
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

Printer::Printer(SDL_Renderer* renderer): _renderer{renderer} {}

void Printer::receiveAllDrops(std::unordered_map<SpotType, std::unordered_set<Drop>> setOfDropsPerType, std::unordered_map<int, BoxInfo> boxes)
{
    print(setOfDropsPerType, boxes);
}

void Printer::print(unordered_map<SpotType, unordered_set<Drop>> dropsPerType, std::unordered_map<int, BoxInfo> boxes)
{  
    vector<vector<Drop>> redDrops(9, vector<Drop>{});
    vector<vector<Drop>> cyanDrops(9, vector<Drop>{});
    vector<vector<Drop>> amberDrops(9, vector<Drop>{});
    vector<vector<Drop>> purpleDrops(9, vector<Drop>{});
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    for (auto& setPerType : dropsPerType)
    {
        // TODO should this be a reference?
        unordered_set<Drop> setOfDrops = setPerType.second;
             
        for (auto& drop: setOfDrops)
        {
            int id = drop.getBoxId();
            int groupId = boxes.at(id).getGroupId();
            int level = boxes.at(id).getLevel();
            //cout << level << ", "; 
            if(groupId%4 == 0 )
            {
                if (level >= 8)
                {
                    redDrops[8].push_back(drop);
                }
                else
                {
                    redDrops[level].push_back(drop);
                }
            }
            else if(groupId%4 == 1 )
            {
                if (level >= 8)
                {
                    cyanDrops[8].push_back(drop);
                }
                else
                {
                    cyanDrops[level].push_back(drop);
                }
            }
            else if(groupId%4 == 2 )
            {
            //cout << "[" << id << "]"<< level << ", ";
                if (level >= 8)
                {
                    amberDrops[8].push_back(drop);
                }
                else
                {
                    amberDrops[level].push_back(drop);
                }
            }
            else
            {
                if (level >= 8)
                {
                    purpleDrops[8].push_back(drop);
                }
                else
                {
                    purpleDrops[level].push_back(drop);
                }
            }
        }
    }
    //cout << endl;

    int redCount = 0; 
    for(size_t ii=0; ii<redDrops.size(); ++ii)
    {
        vector<Drop> dropVector = redDrops[ii];
        int level = ii;
        (void)level;
        for(const Drop& drop : dropVector)
        {
            SDL_Rect squareRect;
            squareRect.w = 3;// TODO width and height is taken from box width and height not hardcoded
            squareRect.h = 3;
            squareRect.x = drop.getPosition().getX();
            squareRect.y = drop.getPosition().getY();
            SDL_SetRenderDrawColor(_renderer, red[level][0], red[level][1], red[level][2], 0xFF);
            SDL_RenderFillRect(_renderer, &squareRect);
            ++redCount;
        }

    }

    int cyanCount = 0;
    for(size_t ii=0; ii<cyanDrops.size(); ++ii)
    {
        vector<Drop> dropVector = cyanDrops[ii];
        int level = ii;
        for(const Drop& drop : dropVector)
        {
            SDL_Rect squareRect;
            squareRect.w = 3;// TODO width and height is taken from box width and height not hardcoded
            squareRect.h = 3;
            squareRect.x = drop.getPosition().getX();
            squareRect.y = drop.getPosition().getY();
            SDL_SetRenderDrawColor(_renderer, cyan[level][0], cyan[level][1], cyan[level][2], 0xFF);
            SDL_RenderFillRect(_renderer, &squareRect);
            ++cyanCount;
        }
    }
   
    int amberCount = 0;
    for(size_t ii=0; ii<amberDrops.size(); ++ii)
    {   
        vector<Drop> dropVector = amberDrops[ii];
        int level = ii;
        for(const Drop& drop : dropVector)
        {
            SDL_Rect squareRect;
            squareRect.w = 3;// TODO width and height is taken from box width and height not hardcoded
            squareRect.h = 3;
            squareRect.x = drop.getPosition().getX();
            squareRect.y = drop.getPosition().getY();
            SDL_SetRenderDrawColor(_renderer, amber[level][0], amber[level][1], amber[level][2], 0xFF);
            SDL_RenderFillRect(_renderer, &squareRect);
            ++amberCount;
        }

    }
    
    int purpleCount = 0;
    for(size_t ii=0; ii<purpleDrops.size(); ++ii)
    {   
        vector<Drop> dropVector = purpleDrops[ii];
        int level = ii;
        for(const Drop& drop : dropVector)
        {
            SDL_Rect squareRect;
            squareRect.w = 3;// TODO width and height is taken from box width and height not hardcoded
            squareRect.h = 3;
            squareRect.x = drop.getPosition().getX();
            squareRect.y = drop.getPosition().getY();
            SDL_SetRenderDrawColor(_renderer, purple[level][0], purple[level][1], purple[level][2], 0xFF);
            SDL_RenderFillRect(_renderer, &squareRect);
            ++purpleCount;
        }

    }
    (void)redCount;
    (void)amberCount;
    (void)cyanCount;
    (void)purpleCount;
        //cout << "sizes: " << redCount << ", " << cyanCount << ", " << amberCount << ", " << (redCount + cyanCount + amberCount) << endl;

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



