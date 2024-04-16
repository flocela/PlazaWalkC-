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
            auto reducedRectangles = MainSetup::getEndRectangles(SCREEN_WIDTH, SCREEN_HEIGHT); 
            
            // Create Boxes
            int countPerGroup = 200;
            vector<Box> boxes = MainSetup::getBoxes(0, 7, countPerGroup);
            
            // Create Board
            Board board{SCREEN_WIDTH, SCREEN_HEIGHT, std::move(boxes)};

            // Create BoardAgent. It will periodically ask Board to send changes to recorder.
            BoardAgent boardAgent(&board);

            // Create recorder, it will listen for changes from Board and send those changes to the printer.
            Recorder recorder{};
            board.registerListener(&recorder);

            // Create the printer and have it listen for changes from teh recorder.
            Printer_OneColor printer(renderer);
            recorder.registerListener(&printer);

            // Add the end rectangles to printer. It will print them at each rendering.
            printer.addEndRectangles(reducedRectangles);

            // Event loop exit flag
            bool running = true;

            vector<unique_ptr<thread>> thread{};

            Threader threader{};
            
            int boxId = 0;
            
            auto reducedEndRectangles = MainSetup::deleteRect(reducedRectangles, reducedRectangles[0]);
            threader.PMSlideAndSafeDecider(thread, reducedRectangles[0].first, reducedRectangles[0].second, reducedEndRectangles, board, boxId, countPerGroup, running);

            boxId += countPerGroup;
            reducedEndRectangles = MainSetup::deleteRect(reducedRectangles, reducedRectangles[1]);
            threader.PMSlideAndSafeDecider(thread, reducedRectangles[1].first, reducedRectangles[1].second, reducedRectangles, board, boxId, countPerGroup, running);
            
            boxId += countPerGroup;
            reducedEndRectangles = MainSetup::deleteRect(reducedRectangles, reducedRectangles[2]);
            threader.PMSlideAndSafeDecider(thread, reducedRectangles[2].first, reducedRectangles[2].second, reducedRectangles, board, boxId, countPerGroup, running);

            boxId += countPerGroup;
            reducedEndRectangles = MainSetup::deleteRect(reducedRectangles, reducedRectangles[3]);
            threader.PMSlideAndSafeDecider(thread, reducedRectangles[3].first, reducedRectangles[3].second, reducedRectangles, board, boxId, countPerGroup, running);

            boxId += countPerGroup;
            reducedEndRectangles = MainSetup::deleteRect(reducedRectangles, reducedRectangles[4]);
            threader.PMSlideAndSafeDecider(thread, reducedRectangles[4].first, reducedRectangles[4].second, reducedRectangles, board, boxId, countPerGroup, running);

            boxId += countPerGroup;
            reducedEndRectangles = MainSetup::deleteRect(reducedRectangles, reducedRectangles[5]);
            threader.PMSlideAndSafeDecider(thread, reducedRectangles[5].first, reducedRectangles[5].second, reducedRectangles, board, boxId, countPerGroup, running);

            boxId += countPerGroup;
            reducedEndRectangles = MainSetup::deleteRect(reducedRectangles, reducedRectangles[6]);
            threader.PMSlideAndSafeDecider(thread, reducedRectangles[6].first, reducedRectangles[6].second, reducedRectangles, board, boxId, countPerGroup, running);
           
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
