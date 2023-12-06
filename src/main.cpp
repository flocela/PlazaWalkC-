#include <chrono>
#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_ttf.h>

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH    600
#define SCREEN_HEIGHT   600

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
            // Declare rect of square
            SDL_Rect squareRect;

            // Square dimensions: Half of the min(SCREEN_WIDTH, SCREEN_HEIGHT)
            squareRect.w = 10;
            squareRect.h = 20;

            // Square position: In the middle of the screen
            squareRect.x = 0;
            squareRect.y = 0;

            TTF_Font *font = TTF_OpenFont(FONT_PATH, 40);
            if(!font) {
                printf("Unable to load font: '%s'!\n"
                       "SDL2_ttf Error: %s\n", FONT_PATH, TTF_GetError());
                return 0;
            }

            SDL_Color textColor           = { 0x00, 0x00, 0x00, 0xFF };
            SDL_Color textBackgroundColor = { 0xFF, 0xFF, 0xFF, 0xFF };
            SDL_Texture *text = NULL;
            SDL_Rect textRect;

            SDL_Surface *textSurface = TTF_RenderText_Shaded(font, "Red square", textColor, textBackgroundColor);
            if(!textSurface) {
                printf("Unable to render text surface!\n"
                       "SDL2_ttf Error: %s\n", TTF_GetError());
            } else {
                // Create texture from surface pixels
                text = SDL_CreateTextureFromSurface(renderer, textSurface);
                if(!text) {
                    printf("Unable to create texture from rendered text!\n"
                           "SDL2 Error: %s\n", SDL_GetError());
                    return 0;
                }

                // Get text dimensions
                textRect.w = textSurface->w;
                textRect.h = textSurface->h;

                SDL_FreeSurface(textSurface);
            }

            textRect.x = (SCREEN_WIDTH - textRect.w) / 2;
            textRect.y = squareRect.y - textRect.h - 10;

            // Event loop exit flag
            bool running  = true;

            // Event loop
            while(running)
            {
                SDL_Event e;

                // Initialize renderer color white for the background
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Clear screen
                SDL_RenderClear(renderer);

                squareRect.x += 10;
                squareRect.y += 10;
                
                // Set renderer color red to draw the square
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

                // Draw filled square
                SDL_RenderFillRect(renderer, &squareRect);

                // Update screen
                SDL_RenderPresent(renderer);

                if (SDL_PollEvent(&e) != 0)
                {
                    switch (e.type)
                    {
                        case SDL_QUIT:
                            running = false;
                            break; 
                    }
                }
           
                SDL_Delay(500); 
                SDL_RenderPresent(renderer);
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
