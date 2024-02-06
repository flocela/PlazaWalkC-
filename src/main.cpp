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
#include "BoardCallback_Printer.h"
#include "Box.h"
#include "Decider_Safe.h"
#include "Mover_Reg.h"
#include "PositionManager_Down.h"
#include "PositionManager_Up.h"
#include "Printer_OpaqueBox.h"

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH    600
#define SCREEN_HEIGHT   600

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

        this_thread::sleep_for(20ms);
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
            // Create PositionManger
            PositionManager_Down dPositionManger{599, 0, 599, 0, 599};
            PositionManager_Up uPositionManger{0, 0, 599, 0, 599};
            
            // Create Board
            Board board{600, 600};
            Printer_OpaqueBox printer{renderer};
            BoardCallback_Printer callbackPrinter{&board, &printer};
            board.registerCallback(&callbackPrinter);

            // Create Boxes
            vector<unique_ptr<Box>> boxes{};
            boxes.push_back(make_unique<Box>(0, 10, 10));
            boxes.push_back(make_unique<Box>(1, 10, 10));

            // Create map of boxes per boxId
            unordered_map<int, Box*> boxesPerBoxId{};
            boxesPerBoxId.insert({0, boxes[0].get()});
            boxesPerBoxId.insert({1, boxes[1].get()});
         
            // Create mover 
            Mover_Reg mover0{*(boxes[0].get()), board};
            Mover_Reg mover1{*(boxes[1].get()), board};

            // Create decider
            Decider_Safe decider{};
             
            std::thread t0(funcMoveBox, Position{10, 10}, &board, &(dPositionManger), &decider, &mover0);
            std::thread t1(funcMoveBox, Position{10, 500}, &board, &(uPositionManger), &decider, &mover1);
                                
            // Event loop exit flag
            bool running  = true;

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
           
                SDL_Delay(20); 
            }

            
            t0.join();
            t1.join();

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
