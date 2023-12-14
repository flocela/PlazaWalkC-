#include <chrono>
#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdbool.h>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Board.h"
#include "Box.h"
#include "Printer.h"

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH    600
#define SCREEN_HEIGHT   600

#define FONT_PATH   "assets/pacifico/Pacifico.ttf"

using namespace std;

void moveUp(Board* board, int boxId)
{   
    int count = 500;
    while (count > 0)
    {   this_thread::sleep_for(20ms);
        Position pos = board->getLocation(boxId);
        vector<Position> positions{{pos.getX(), (pos.getY() - 1)}};
        board->move(boxId, positions);
        --count;
    }
}


void updateSquares(Board& board, SDL_Renderer* renderer)
{   
    vector<Box> boxes = board.getCopyOfBoxes();
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    
    for (const Box& box : boxes)
    {
        SDL_Rect squareRect;

        // Square dimensions: Half of the min(SCREEN_WIDTH, SCREEN_HEIGHT)
        squareRect.w = 10;
        squareRect.h = 10;

        // Square position: Top left corner
        squareRect.x = box.getX();
        squareRect.y = box.getY();
        
        SDL_RenderFillRect(renderer, &squareRect);
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
            Board board{600, 600};
            board.insert(0, 10, 10, 5, 599);
            board.insert(1, 10, 10, 50, 50);

            thread t0(moveUp, &board, 0);

            Printer printer{};

            // Event loop exit flag
            bool running  = true;

            // Event loop
            while(running)
            {
                // Print Screen
                vector<Position> positions1{{(1 + board.getLocation(1).getX()), board.getLocation(1).getY()}};
                board.move(1, positions1);

                printer.print(renderer, board.getCopyOfBoxes());

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
