/*
 * Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#include "Board.h"

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH    600
#define SCREEN_HEIGHT   600

#define FONT_PATH   "assets/pacifico/Pacifico.ttf"

using namespace std;

void printBoard(Board& board, SDL_Renderer* renderer, SDL_Rect* rect0, SDL_Rect* rect1)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    
    Position zeroPosition = board.getLocation(0);
    Position onePosition = board.getLocation(1);

    rect0->x = zeroPosition.getX();
    rect0->y = zeroPosition.getY();
    rect1->x = onePosition.getX();
    rect1->y = onePosition.getY();

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

    // Draw filled square
    SDL_RenderFillRect(renderer, rect0);
    SDL_RenderFillRect(renderer, rect1);
    
    // Update screen
    SDL_RenderPresent(renderer);

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
            SDL_Rect rect0;
            SDL_Rect rect1;

            rect0.w = 10;
            rect1.w = 10;
            rect0.h = 10;
            rect1.h = 10;

            
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
          
            Board board{100, 100};
            board.insert(0, 10, 10, 10, 0); // box zero is going down
            board.insert(1, 10, 10, 10, 40); // box one is going up

            printBoard(board, renderer, &rect0, &rect1); 
          
            vector<Position> zeroPotentialPositions{Position{10, 10}, Position{20, 10}, Position{0, 10}}; 
            vector<Position> onePotentialPositions{Position{10, 30}, Position{20, 30}, Position{0, 30}}; 
            board.move(0, zeroPotentialPositions);
            board.move(1, onePotentialPositions);
             
            printBoard(board, renderer, &rect0, &rect1); 

            zeroPotentialPositions = {Position{10, 20}, Position{20, 20}, Position{0, 20}}; 
            onePotentialPositions = {Position{10, 20}, Position{20, 20}, Position{0, 20}}; 
            board.move(0, zeroPotentialPositions);
            board.move(1, onePotentialPositions);
            
            printBoard(board, renderer, &rect0, &rect1); 

            zeroPotentialPositions = {Position{10, 30}, Position{20, 30}, Position{0, 30}}; 
            onePotentialPositions = {Position{20, 10}, Position{0, 10}, Position{30, 10}}; 
            board.move(0, zeroPotentialPositions);
            board.move(1, onePotentialPositions);

            printBoard(board, renderer, &rect0, &rect1);

            // Event loop exit flag
            bool quit = false;

            // Event loop
            while(!quit)
            {
                SDL_Event e;

                // Wait indefinitely for the next available event
                SDL_WaitEvent(&e);

                // User requests quit
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }
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
