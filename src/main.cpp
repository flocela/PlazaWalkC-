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
#include "PositionManager_Down.h"
#include "PositionManager_Up.h"
#include "Printer_OneColor.h"
#include "Recorder.h"

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   800

#define FONT_PATH   "assets/pacifico/Pacifico.ttf"

using namespace std;

void funcMoveBox(
        Position position,
        Board* board,
        PositionManager* posManager,
        Decider* decider,
        Mover* mover
        )
{
    //cout << "funcMoveBox: " << endl;
    Position curPosition = position;
    // TODO what to do if box isn't successfully added to the board?
    mover->addBox(curPosition);
    while (!posManager->atEnd(curPosition))
    {
        Position nextPosition = decider->getNextPosition(
                                            posManager->getFuturePositions(curPosition),
                                            *board);

        if (nextPosition != Position{-1, -1})
        {
            if (mover->moveBox(curPosition, nextPosition))
            {
                curPosition = nextPosition;
            }
        }
        this_thread::sleep_for(100ms);
    }
}

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
   
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x99, 0x99, 0xFF);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
            SDL_RenderPresent(renderer);
            
            // Create Board
            Board board{800, 800};
            BoardAgent boardAgent(&board);
            Recorder recorder{};
            board.registerListener(&recorder);
            Printer_OneColor printer(renderer);
            recorder.registerListener(&printer);
            
            // Create PositionManger
            PositionManager_Down dPositionManager{100, 0, board.getWidth(), 0, board.getHeight()};
            PositionManager_Up uPositionManager{0, 0, board.getWidth(), 0, board.getHeight()};

            // Create decider
            Decider_Safe decider{};

            // Create Boxes
            vector<unique_ptr<Box>> boxes{};
            for (int ii=0; ii<4; ++ii)
            {
                boxes.push_back(make_unique<Box>(ii, 3, 3));
            }

            // Create movers 
            vector<unique_ptr<Mover_Reg>> movers{};
            for (uint32_t ii=0; ii<boxes.size(); ++ii)
            {
                movers.push_back(make_unique<Mover_Reg>(*(boxes[ii].get()), board));
            }  

            vector<unique_ptr<thread>> threads{};
            uint32_t boxIdx = 0;
            for (uint32_t ii=0; ii<360; ii+= 3)
            {
                // TODO change Position's attribute types to be uint32_t
                if (boxIdx < boxes.size())
                {
                    threads.push_back(make_unique<thread>(funcMoveBox, Position{(int)ii, 30}, &board, &(dPositionManager), &decider, movers[boxIdx].get()));
                }
                ++boxIdx; 
                if (boxIdx < boxes.size())
                {
                    threads.push_back(make_unique<thread>(funcMoveBox, Position{(int)ii, 70}, &board, &(uPositionManager), &decider, movers[boxIdx].get()));
                } 
                ++boxIdx;
            }                                
            

            // Event loop exit flag
            bool running  = true;

            
            //clock_t start, end;     

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
                //start = clock(); 
                boardAgent.updateWithChanges();
                //end = clock();
                //double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
                //cout << "time taken to print is : " << fixed << time_taken << setprecision(5);
                //cout << "sec" << endl;               
                //SDL_Delay(20); 
            }
            
            for(uint32_t ii=0; ii<threads.size(); ++ii)
            {
                threads[ii]->join();
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
