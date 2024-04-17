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
#include "BoardAgent.h"
#include "Box.h"
#include "Decider_Safe.h"
#include "MainSetup.h"
#include "Mover_Reg.h"
#include "PositionManager_Diagonal.h"
#include "PositionManager_Down.h"
#include "PositionManager_Slide.h"
#include "Printer_OneColor.h"
#include "Recorder.h"
#include "Threader.h"
#include "Util.h"


// Define screen dimensions
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   800

using namespace std;


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
    }
    else
    {
        // Create renderer
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer)
        {
            printf("Renderer could not be created!\nSDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // Boxes on grid start at one of these rectangles and end at another one of these rectangles.
            auto toFromRectangles = MainSetup::getEndRectangles(SCREEN_WIDTH, SCREEN_HEIGHT); 
            
            // Create Boxes
            // Group0 with 200 boxes (red) will tread safely.
            // Group1 with 800 boxes (blue) will tread recklessly.
            // Group2 with 400 boxes (yellow) will tread safely.
            // Group3 with 350 boxes (purple) will tread recklessly.
            vector<Box> boxes{};
            MainSetup::addAGroupOfBoxes(boxes, 0, 0, 200);
            MainSetup::addAGroupOfBoxes(boxes, 200, 1, 800);
            MainSetup::addAGroupOfBoxes(boxes, 1000, 2, 400);
            MainSetup::addAGroupOfBoxes(boxes, 1400, 3, 350);
            
            // Create Board
            Board board{SCREEN_WIDTH, SCREEN_HEIGHT, std::move(boxes)};

            // Create BoardAgent. It will periodically ask Board to send changes to recorder.
            BoardAgent boardAgent(&board);

            // Create recorder, it will listen for changes from Board and send those changes to the printer.
            Recorder recorder{};
            board.registerListener(&recorder);

            // Create the printer and have it listen for changes from the recorder.
            Printer_OneColor printer(renderer);
            recorder.registerListener(&printer);

            // Add the end rectangles to printer. It will print them at each rendering.
            printer.addEndRectangles(toFromRectangles);

            // Event loop exit flag
            bool running = true;

            vector<unique_ptr<thread>> thread{};

            Threader threader{};
           
            // Add threads for boxes 0 through 1399. That's red, blue, and yellow boxes.
            threader.populateThreads(
                thread,
                MainSetup::getEndRectangles(SCREEN_WIDTH, SCREEN_HEIGHT),
                MainSetup::getEndRectangles(SCREEN_WIDTH, SCREEN_HEIGHT),
                board,
                vector<pair<int, int>>{
                    {0, 199},      // North wall
                    {200, 399},    // East Wall
                    {400, 599},    // East Wall
                    {600, 799},    // West Wall
                    {800, 999},    // West Wall
                    {1000, 1199},  // South Wall
                    {1200, 1399}}, // South Wall
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
                    DeciderType::risk1,
                    DeciderType::risk1,
                    DeciderType::safe,
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
                boardAgent.updateWithChanges();
                //SDL_Delay(20); 
            }

            for(uint32_t ii=0; ii<thread.size(); ++ii)
            {
                thread[ii]->join();
            }

            // Destroy renderer
            SDL_DestroyRenderer(renderer);
        }

        // Destroy window
        SDL_DestroyWindow(window);
    }

    // Quit SDL2_ttf
    TTF_Quit();

    // Quit SDL
    SDL_Quit();

    return 0;
}
