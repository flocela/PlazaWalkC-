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
#include "PositionManager_Straight.h"
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
        Mover* mover,
        bool* breaker
        )
{
    //cout << "funcMoveBox: " << endl;
    Position curPosition = position;
    // TODO what to do if box isn't successfully added to the board?
    mover->addBox(curPosition);
    while (!posManager->atEnd(curPosition) && *breaker)
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
        this_thread::sleep_for(10ms);
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
            
            // End points
            pair<Position, Position> eastEndPoint{Position{360, 360}, Position{365, 390}};
            pair<Position, Position> upEndPoint{Position{170, 0}, Position{190, 5}};
            pair<Position, Position> westEndPoint{Position{0, 170}, Position{5, 190}};
            
            // Create Board
            Board board{800, 800};
            BoardAgent boardAgent(&board);
            Recorder recorder{};
            board.registerListener(&recorder);
            Printer_OneColor printer(renderer);
            printer.addEndPoint(eastEndPoint.first, eastEndPoint.second);
            printer.addEndPoint(upEndPoint.first, upEndPoint.second);
            printer.addEndPoint(westEndPoint.first, westEndPoint.second);
            recorder.registerListener(&printer);

            // Create PositionManger
            PositionManager_Straight eastPositionManager{eastEndPoint.first, eastEndPoint.second, 0, board.getWidth()-1, 0, board.getHeight()-1};
            PositionManager_Straight upPositionManager{upEndPoint.first, upEndPoint.second, 0, board.getWidth()-1, 0, board.getHeight()-1};
            PositionManager_Straight westPositionManager{westEndPoint.first, westEndPoint.second, 0, board.getWidth()-1, 0, board.getHeight()-1};

            // Create Boxes
            vector<unique_ptr<Box>> boxes{};
            for (int ii=0; ii<300; ++ii)
            {
                boxes.push_back(make_unique<Box>(ii, 3, 3));
            }

            // CreatePositionManagers
            vector<unique_ptr<PositionManager_Straight>> eastPMs{};
            vector<unique_ptr<PositionManager_Straight>> upPMs{};
            vector<unique_ptr<PositionManager_Straight>> westPMs{};

            for(int ii=0; ii<300; ++ii)
            {
                eastPMs.push_back(make_unique<PositionManager_Straight>(
                    eastEndPoint.first,
                    eastEndPoint.second,
                    0,
                    board.getWidth()-1,
                    0,
                    board.getHeight()-1));
                upPMs.push_back(make_unique<PositionManager_Straight>(
                    upEndPoint.first,
                    upEndPoint.second,
                    0,
                    board.getWidth()-1,
                    0,
                    board.getHeight()-1));
                westPMs.push_back(make_unique<PositionManager_Straight>(
                    westEndPoint.first,
                    westEndPoint.second,
                    0,
                    board.getWidth()-1,
                    0,
                    board.getHeight()-1));
            }

            // Create decider
            vector<unique_ptr<Decider_Safe>> deciders{};
            for(uint32_t ii=0; ii<boxes.size(); ++ii)
            {
                deciders.push_back(make_unique<Decider_Safe>());
            }

            // Create movers 
            vector<unique_ptr<Mover_Reg>> movers{};
            for (uint32_t ii=0; ii<boxes.size(); ++ii)
            {
                movers.push_back(make_unique<Mover_Reg>(*(boxes[ii].get()), board));
            }  
            
            // Event loop exit flag
            bool running  = true;
            
            vector<unique_ptr<thread>> threads{};
            uint32_t boxIdx = 0;
            for (uint32_t ii=0; ii<360; ii+= 3)
            {
                // TODO change Position's attribute types to be uint32_t
                if (boxIdx < boxes.size())
                {
                    threads.push_back(make_unique<thread>(
                        funcMoveBox,
                        Position{1,(int)ii},
                        &board,
                        eastPMs[boxIdx].get(),
                        deciders[boxIdx].get(),
                        movers[boxIdx].get(),
                        &running));
                }
                ++boxIdx; 
                if (boxIdx < boxes.size())
                {
                    threads.push_back(make_unique<thread>(
                        funcMoveBox,
                        Position{(int)ii, 358},
                        &board,
                        upPMs[boxIdx].get(),
                        deciders[boxIdx].get(),
                        movers[boxIdx].get(),
                        &running));
                }
                ++boxIdx; 
                if (boxIdx < boxes.size())
                {
                    threads.push_back(make_unique<thread>(
                        funcMoveBox,
                        Position{358,(int)ii},
                        &board,
                        westPMs[boxIdx].get(),
                        deciders[boxIdx].get(),
                        movers[boxIdx].get(),
                        &running));
                }
                ++boxIdx; 
                if (boxIdx < boxes.size())
                {
                    threads.push_back(make_unique<thread>(
                        funcMoveBox,
                        Position{(int)ii, 1},
                        &board,
                        westPMs[boxIdx].get(),
                        deciders[boxIdx].get(),
                        movers[boxIdx].get(),
                        &running));
                }
                ++boxIdx; 

            }

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
