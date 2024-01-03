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
#include "Box.h"
#include "Mover_Down.h"
#include "Mover_Up.h"
#include "Printer.h"

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH    600
#define SCREEN_HEIGHT   600

#define FONT_PATH   "assets/pacifico/Pacifico.ttf"

using namespace std;

void moving(Box* box, Mover* mover, Board* board)
{
    int count = 500;
    while (count > 0)
    {
        --count;
        Position curPos = box->getPos(std::chrono::high_resolution_clock::now());
        if (curPos.getX() > SCREEN_WIDTH || curPos.getX() < 0)
        {
            break;
        }
        if (curPos.getY() > SCREEN_HEIGHT || curPos.getY() < 0)
        {
            break;
        }
       
        for (const Position& newPos : mover->getFuturePositions(*box))
        {   
            std::unordered_map<int, BoardNote> boardNotesPerBoxId = board->getNotes(newPos);
            bool okay = true;
            for (const auto& boardNotePerBoxId  : boardNotesPerBoxId)
            {
                if (boardNotePerBoxId.second.getType() == 4)
                {
                    okay = false;
                    break;
                }
            }
            if (okay)
            {
                // add toLeave BoardNote in board 
                board->addNote(curPos, BoardNote{1, box->getId()});

                // add toArrive BoardNote in board
                board->addNote(newPos, BoardNote{2, box->getId()});
                
                const std::chrono::time_point<std::chrono::high_resolution_clock> toLeaveTime = std::chrono::high_resolution_clock::now();
                
                // add a toLeave BoxNote
                box->addNote(BoxNote{10, newPos, curPos, toLeaveTime});

                this_thread::sleep_for(5ms);

                const std::chrono::time_point<std::chrono::high_resolution_clock> arriveTime = std::chrono::high_resolution_clock::now();
                
                // add an arrive BoxNote in box
                box->addNote(BoxNote{11, newPos, curPos, arriveTime});

                // add left BoardNote in board
                board->addNote(curPos, BoardNote{3, box->getId()});

                // add arrive BoardNote in board
                board->addNote(newPos, BoardNote{4, box->getId()});

                break;
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
            // Create Mover
            Mover_Down dMover{};
            Mover_Up uMover{};

            // Create Board
            Board board{600, 600};

            // Create Boxes
            vector<unique_ptr<Box>> boxes{};
            boxes.push_back(make_unique<Box>(0, 10, 10));
            boxes[boxes.size()-1]->addNote(BoxNote{11, Position{10, 0}, Position{10, 0}, std::chrono::high_resolution_clock::now()});
            boxes.push_back(make_unique<Box>(1,10,10));
            boxes[boxes.size()-1]->addNote(BoxNote{11, Position{10, 500}, Position{10, 500}, std::chrono::high_resolution_clock::now()});
            
            std::thread t0{moving, boxes[0].get(), &(dMover), &(board)};
            std::thread t1{moving, boxes[1].get(), &(uMover), &(board)};
                                
            Printer printer{};

            // Event loop exit flag
            bool running  = true;

            // Event loop
            while(running)
            {
                // Print Screen // this should be a copy of boxes or take into account a time stamp.
                printer.print(renderer, boxes);

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

            Position pos0 = boxes[0]->getPos(std::chrono::high_resolution_clock::now());
            Position pos1 = boxes[1]->getPos(std::chrono::high_resolution_clock::now());
            cout << "box0: " << pos0.getX() << ", " << pos0.getY() << endl;
            cout << "box1: " << pos1.getX() << ", " << pos1.getY() << endl;

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
