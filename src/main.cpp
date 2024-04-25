#include <iomanip>
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <vector>
#include <thread>
#include <utility>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Board.h"
#include "BoardProxy.h"
#include "BroadcastAgent.h"
#include "Box.h"
#include "Decider_Safe.h"
#include "MainSetup.h"
#include "Mover_Reg.h"
#include "Printer.h"
#include "Recorder.h"
#include "Threader.h"
#include "Util.h"


// Define screen dimensions
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   800

using namespace std;

void quitTTFandSDL()
{
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    // Unused argc, argv
    (void) argc;
    (void) argv;
    
    // Initialize SDL2 and SDL2_ttf
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL2 could not be initialized!\nSDL2 Error: %s\n", SDL_GetError());
        return 0;
    }

    TTF_Init();

    #if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        printf("SDL can not disable compositor bypass!\n");
        return 0; }
    #endif

    // Create window
    SDL_Window *window = SDL_CreateWindow("Across The Plaza",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if(!window)
    {
        printf("Window could not be created!\nSDL_Error: %s\n", SDL_GetError());
        quitTTFandSDL();
        return 0;
    }

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        printf("Renderer could not be created!\nSDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        quitTTFandSDL();
        return 0;
    }

    /* SDL, TTF, window, and renderer work! */

    // In-bound and out-bound rectangles are where the boxes start from and terminate at. A box can not start and end at the same rectangle in inOutBoundRectangles.
    auto inOutBoundRectangles = MainSetup::getEndRectangles(SCREEN_WIDTH, SCREEN_HEIGHT); 
    
    // Create Boxes
    // Group0 with 200 boxes (red) will tread safely. Boxes start at north wall.
    // Group1 with 400 boxes (blue) will tread safely. Boxes start at top of west and east walls. 
    // Group2 with 400 boxes (yellow) will tread recklessly. Boxes start at bottom of west and east walls.
    // Group3 with 400 boxes (purple) will tread recklessly. Boxes start at south wall.
    vector<Box> boxes{};
    MainSetup::addAGroupOfBoxes(boxes, 0, 0, 200);
    MainSetup::addAGroupOfBoxes(boxes, 200, 1, 400);
    MainSetup::addAGroupOfBoxes(boxes, 600, 2, 400);
    MainSetup::addAGroupOfBoxes(boxes, 1000, 3, 400);
    
    // Create Board
    Board board{SCREEN_WIDTH, SCREEN_HEIGHT, std::move(boxes)};

    // Create BroadcastAgent. It will periodically ask Board (via BoardProxy) to send changes to recorder.
    BroadcastAgent broadcastAgent{BoardProxy(board)};

    // Create Recorder, it will listen for changes from Board and send those changes to the printer.
    Recorder recorder{};
    board.registerListener(&recorder);

    // Create the printer and have it listen for changes from the recorder.
    Printer printer(renderer);
    vector<vector<uint8_t>> red{
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
    vector<vector<uint8_t>> cyan{
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
    vector<vector<uint8_t>> amber{
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
    vector<vector<uint8_t>> purple{
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

    unordered_map<int, Color> colorPerGroupNumber{};
    colorPerGroupNumber.insert({0, Color{red}});
    colorPerGroupNumber.insert({1, Color{cyan}});
    colorPerGroupNumber.insert({2, Color{amber}});
    colorPerGroupNumber.insert({3, Color{purple}});
   
    printer.setGroupColors(colorPerGroupNumber); 
    
    recorder.registerListener(&printer);

    // Add the in-bound and out-bound rectangles to printer (where the boxes start and end).
    printer.addInOutBoundRectangles(inOutBoundRectangles);

    // Event loop exit flag
    bool running = true;

    vector<unique_ptr<thread>> thread{};

    Threader threader{};
   
    // Add threads for boxes 0 through 1399. That's red, blue, yellow, and purple boxes.
    // Box id comments refer to where the box starts at and what color its group is.
    threader.populateThreads(
        thread,
        MainSetup::getEndRectangles(SCREEN_WIDTH, SCREEN_HEIGHT),
        MainSetup::getEndRectangles(SCREEN_WIDTH, SCREEN_HEIGHT),
        board,
        vector<pair<int, int>>{
            {0, 199},      // North wall, red boxes
            {200, 399},    // West wall top, blue boxes
            {400, 599},    // East wall top, blue boxes
            {600, 799},    // West wall bottom, yellow boxes
            {800, 999},    // East wall bottom, yellow boxes
            {1000, 1199},  // South wall left, purple boxes
            {1200, 1399}}, // South wall right, purple boxes
        vector<PositionManagerType>{
            PositionManagerType::slide,
            PositionManagerType::slide,
            PositionManagerType::slide,
            PositionManagerType::slide,
            PositionManagerType::slide,
            PositionManagerType::slide,
            PositionManagerType::slide},
        vector<DeciderType>{
            DeciderType::safe,
            DeciderType::safe,
            DeciderType::safe,
            DeciderType::risk1,
            DeciderType::risk1,
            DeciderType::risk1,
            DeciderType::risk1},
        running);
    
    // Event loop
    while(running)
    {
        SDL_Event e;
        if (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    running = false;
                    break; 
            }
        }

        broadcastAgent.requestBroadcast();
    }

    for(uint32_t ii=0; ii<thread.size(); ++ii)
    {
        thread[ii]->join();
    }

    // Destroy renderer
    SDL_DestroyRenderer(renderer);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL2_ttf
    TTF_Quit();

    // Quit SDL
    SDL_Quit();

    return 0;
}
