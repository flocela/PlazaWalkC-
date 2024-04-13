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
#include "Mover_Reg.h"
#include "PositionManager_Diagonal.h"
#include "PositionManager_Down.h"
#include "PositionManager_Slide.h"
#include "Printer_OneColor.h"
#include "Recorder.h"
#include "Threader.h"
#include "Util.h"

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   800

#define FONT_PATH   "assets/pacifico/Pacifico.ttf"

using namespace std;


int main(int argc, char* argv[])
{
    // Unused argc, argv
    (void) argc;
    (void) argv;
    
    // Initialize SDL2
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL2 could not be initialized!\n"
               "SDL2 Error: %s\n", SDL_GetError());
        return 0;
    }

    // Initialize SDL2_ttf
    TTF_Init();

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        printf("SDL can not disable compositor bypass!\n");
        return 0;
    }
#endif

    // Create window
    SDL_Window *window = SDL_CreateWindow("SDL2_ttf sample",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if(!window)
    {
        printf("Window could not be created!\n"
               "SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create renderer
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer)
        {
            printf("Renderer could not be created!\n"
                   "SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            
            // End rectangles
            vector<pair<Position, Position>> endRanges{};
            endRanges.push_back({Position{350, 0},   Position{450, 10}}); 
            endRanges.push_back({Position{789, 175}, Position{799, 225}}); 
            endRanges.push_back({Position{789, 575}, Position{799, 625}});
            endRanges.push_back({Position{575, 789}, Position{625, 799}});
            endRanges.push_back({Position{175, 789}, Position{225, 799}});
            endRanges.push_back({Position{0, 575},   Position{10, 625}});
            endRanges.push_back({Position{0, 175},   Position{10, 225}});
            
            // Create Boxes
            vector<Box> boxes = Util::getBoxes(0, 7, 200);
            
            // Create Board
            Board board{800, 800, boxes};


            // Create Listeners including Printer 
            BoardAgent boardAgent(&board);
            Recorder recorder{};
            board.registerListener(&recorder);
            Printer_OneColor printer(renderer);
            printer.addEndPoint(endRanges[0].first, endRanges[0].second);
            printer.addEndPoint(endRanges[1].first, endRanges[1].second);
            printer.addEndPoint(endRanges[2].first, endRanges[2].second);
            printer.addEndPoint(endRanges[3].first, endRanges[3].second);
            printer.addEndPoint(endRanges[4].first, endRanges[4].second);
            printer.addEndPoint(endRanges[5].first, endRanges[5].second);
            printer.addEndPoint(endRanges[6].first, endRanges[6].second);
            recorder.registerListener(&printer);

            // Event loop exit flag
            bool running = true;

            vector<unique_ptr<thread>> thread{};

            Threader threader{};
            
            int count = 200;
            int boxId = 0;
            int ii = 0;
            
            vector<pair<Position, Position>> smallerEndRanges = vector<pair<Position, Position>>(endRanges.begin()+1, endRanges.end());
            threader.PMSlideAndSafeDecider(thread, endRanges[0].first, endRanges[0].second, smallerEndRanges, board, boxId, count, running);

            boxId += count;
            ++ii;
            copy(endRanges.cbegin(), endRanges.cbegin()+ii, smallerEndRanges.begin());
            copy(endRanges.cbegin()+ii+1, endRanges.cend(), smallerEndRanges.begin()+ii);
            threader.PMSlideAndSafeDecider(thread, endRanges[1].first, endRanges[1].second, smallerEndRanges, board, boxId, count, running);
            
            boxId += count;
            ++ii;
            copy(endRanges.cbegin(), endRanges.cbegin()+ii, smallerEndRanges.begin());
            copy(endRanges.cbegin()+ii+1, endRanges.cend(), smallerEndRanges.begin()+ii);
            threader.PMSlideAndSafeDecider(thread, endRanges[2].first, endRanges[2].second, smallerEndRanges, board, boxId, count, running);

            boxId += count;
            ++ii;
            copy(endRanges.cbegin(), endRanges.cbegin()+ii, smallerEndRanges.begin());
            copy(endRanges.cbegin()+ii+1, endRanges.cend(), smallerEndRanges.begin()+ii);
            threader.PMSlideAndSafeDecider(thread, endRanges[3].first, endRanges[3].second, smallerEndRanges, board, boxId, count, running);

            boxId += count;
            ++ii;
            copy(endRanges.cbegin(), endRanges.cbegin()+ii, smallerEndRanges.begin());
            copy(endRanges.cbegin()+ii+1, endRanges.cend(), smallerEndRanges.begin()+ii);
            threader.PMSlideAndSafeDecider(thread, endRanges[4].first, endRanges[4].second, smallerEndRanges, board, boxId, count, running);

            boxId += count;
            ++ii;
            copy(endRanges.cbegin(), endRanges.cbegin()+ii, smallerEndRanges.begin());
            copy(endRanges.cbegin()+ii+1, endRanges.cend(), smallerEndRanges.begin()+ii);
            threader.PMSlideAndSafeDecider(thread, endRanges[5].first, endRanges[5].second, smallerEndRanges, board, boxId, count, running);

            boxId += count;
            ++ii;
            copy(endRanges.cbegin(), endRanges.cbegin()+ii, smallerEndRanges.begin());
            copy(endRanges.cbegin()+ii+1, endRanges.cend(), smallerEndRanges.begin()+ii);
            threader.PMSlideAndSafeDecider(thread, endRanges[6].first, endRanges[6].second, smallerEndRanges, board, boxId, count, running);
           
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
