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
    SDL_Window *window = SDL_CreateWindow("SDL2_ttf sample",
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
            auto endRectangles = MainSetup::getEndRectangles(SCREEN_WIDTH, SCREEN_HEIGHT); 
            
            // Create Boxes
            vector<Box> boxes = MainSetup::getBoxes(0, 7, 200);
            
            // Create Board
            Board board{SCREEN_WIDTH, SCREEN_HEIGHT, boxes};

            // Create BoardAgent. It will periodically ask Board to send changes to recorder.
            BoardAgent boardAgent(&board);

            // Create recorder, it will listen for changes from Board and send those changes to the printer.
            Recorder recorder{};
            board.registerListener(&recorder);

            // Create the printer and have it listen for changes from teh recorder.
            Printer_OneColor printer(renderer);
            recorder.registerListener(&printer);

            // Add the end rectangles to printer. It will print them at each rendering.
            printer.addEndRectangles(endRectangles);

            // Event loop exit flag
            bool running = true;

            vector<unique_ptr<thread>> thread{};

            Threader threader{};
            
            int count = 200;
            int boxId = 0;
            int ii = 0;
            
            vector<pair<Position, Position>> smallerEndRectangles = vector<pair<Position, Position>>(endRectangles.begin()+1, endRectangles.end());
            threader.PMSlideAndSafeDecider(thread, endRectangles[0].first, endRectangles[0].second, smallerEndRectangles, board, boxId, count, running);

            boxId += count;
            ++ii;
            copy(endRectangles.cbegin(), endRectangles.cbegin()+ii, smallerEndRectangles.begin());
            copy(endRectangles.cbegin()+ii+1, endRectangles.cend(), smallerEndRectangles.begin()+ii);
            threader.PMSlideAndSafeDecider(thread, endRectangles[1].first, endRectangles[1].second, smallerEndRectangles, board, boxId, count, running);
            
            boxId += count;
            ++ii;
            copy(endRectangles.cbegin(), endRectangles.cbegin()+ii, smallerEndRectangles.begin());
            copy(endRectangles.cbegin()+ii+1, endRectangles.cend(), smallerEndRectangles.begin()+ii);
            threader.PMSlideAndSafeDecider(thread, endRectangles[2].first, endRectangles[2].second, smallerEndRectangles, board, boxId, count, running);

            boxId += count;
            ++ii;
            copy(endRectangles.cbegin(), endRectangles.cbegin()+ii, smallerEndRectangles.begin());
            copy(endRectangles.cbegin()+ii+1, endRectangles.cend(), smallerEndRectangles.begin()+ii);
            threader.PMSlideAndSafeDecider(thread, endRectangles[3].first, endRectangles[3].second, smallerEndRectangles, board, boxId, count, running);

            boxId += count;
            ++ii;
            copy(endRectangles.cbegin(), endRectangles.cbegin()+ii, smallerEndRectangles.begin());
            copy(endRectangles.cbegin()+ii+1, endRectangles.cend(), smallerEndRectangles.begin()+ii);
            threader.PMSlideAndSafeDecider(thread, endRectangles[4].first, endRectangles[4].second, smallerEndRectangles, board, boxId, count, running);

            boxId += count;
            ++ii;
            copy(endRectangles.cbegin(), endRectangles.cbegin()+ii, smallerEndRectangles.begin());
            copy(endRectangles.cbegin()+ii+1, endRectangles.cend(), smallerEndRectangles.begin()+ii);
            threader.PMSlideAndSafeDecider(thread, endRectangles[5].first, endRectangles[5].second, smallerEndRectangles, board, boxId, count, running);

            boxId += count;
            ++ii;
            copy(endRectangles.cbegin(), endRectangles.cbegin()+ii, smallerEndRectangles.begin());
            copy(endRectangles.cbegin()+ii+1, endRectangles.cend(), smallerEndRectangles.begin()+ii);
            threader.PMSlideAndSafeDecider(thread, endRectangles[6].first, endRectangles[6].second, smallerEndRectangles, board, boxId, count, running);
           
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
