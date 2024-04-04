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
#include "PositionManager_Diagonal.h"
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
        PositionManager_Diagonal posManager,
        Decider_Safe decider,
        Mover_Reg mover,
        bool* breaker
)
{  
 
    Position curPosition = position;
    // TODO what to do if box isn't successfully added to the board?
    int n = 1;
    while(!mover.addBox(curPosition) && *breaker)
    {
        this_thread::sleep_for(n * 10ms);
     //   cout << n << ", ";
        ++n;
    }

    while (!posManager.atEnd(curPosition) && *breaker)
    {
        Position nextPosition = decider.getNextPosition(
                                            posManager.getFuturePositions(curPosition),
                                            *board);

        if (nextPosition != Position{-1, -1})
        {
            if (mover.moveBox(curPosition, nextPosition))
            {
                curPosition = nextPosition;
            }
        }
        this_thread::sleep_for(10ms);
    }

    // if box has reached its destination then it disapears from the board.
    if (posManager.atEnd(curPosition))
    {
        mover.removeBox(curPosition);
    }

}

//void insertThread(vector<unique_ptr<thread>>& threads, Position endPoint1, Position endPoint2, vector<PositionManager_Diagonal> pm, Decider_Safe decider, bool& running, int firstBoxId, int count, Board* board)

void insertThread(vector<unique_ptr<thread>>& threads, Position endPoint1, Position endPoint2, Board* board, vector<PositionManager_Diagonal> pm, Decider_Safe decider, int firstBoxId, bool& running, int count)
{
    for(int ii=0; ii<count; ++ii)
    {
        int nx = std::abs(endPoint1.getX() - endPoint2.getX());
        int ny = std::abs(endPoint1.getY() - endPoint2.getY());
   
        int minX = min(endPoint1.getX(), endPoint2.getX());
        int minY = min(endPoint1.getY(), endPoint2.getY());

        int rx = minX + ( (nx==0) ? 0 : (rand() % nx) );
        int ry = minY + ( (ny==0) ? 0 : (rand() % ny) ); 
        //cout << "[" << rx << ", " << ry << "] " << "; ";

        int randPM = rand() % pm.size();

        // TODO funcMoveBox, make PositionManager a copy by value not reference
        threads.push_back(make_unique<thread>(funcMoveBox, Position{rx, ry}, board, pm[randPM], decider, Mover_Reg{firstBoxId+ii, board}, &running));
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
            pair<Position, Position> N1{Position{350, 0},   Position{450, 10}};
            pair<Position, Position> E2{Position{789, 175}, Position{799, 225}};
            pair<Position, Position> E3{Position{789, 575}, Position{799, 625}};
            pair<Position, Position> S4{Position{575, 789}, Position{625, 799}};
            pair<Position, Position> S5{Position{175, 789}, Position{225, 799}};
            pair<Position, Position> W6{Position{0, 575},   Position{10, 625}};
            pair<Position, Position> W7{Position{0, 175},   Position{10, 225}};
            
            // Create Boxes
            vector<Box> boxes{};
            for (int ii=0; ii<300; ++ii)
            {
                if (ii<100)
                {
                    boxes.push_back(Box{ii, 0, 3, 3});
                }
                else if (ii<200)
                {
                    boxes.push_back(Box{ii, 1, 3, 3});
                }
                else
                {
                    boxes.push_back(Box{ii, 2, 3, 3});
                }
            }
            
            // Create Board
            Board board{800, 800, boxes};

            // Create PositionManager_Diagonals
            int boardXMax = board.getWidth()-1;
            int boardYMax = board.getHeight()-1;

            vector<PositionManager_Diagonal> pm{};
            pm.push_back(PositionManager_Diagonal{N1.first, N1.second, 0, boardXMax, 0, boardYMax});
            pm.push_back(PositionManager_Diagonal{E2.first, E2.second, 0, boardXMax, 0, boardYMax});
            pm.push_back(PositionManager_Diagonal{E3.first, E3.second, 0, boardXMax, 0, boardYMax});
            pm.push_back(PositionManager_Diagonal{S4.first, S4.second, 0, boardXMax, 0, boardYMax});
            pm.push_back(PositionManager_Diagonal{S5.first, S5.second, 0, boardXMax, 0, boardYMax});
            pm.push_back(PositionManager_Diagonal{W6.first, W6.second, 0, boardXMax, 0, boardYMax});
            pm.push_back(PositionManager_Diagonal{W7.first, W7.second, 0, boardXMax, 0, boardYMax});


            // Create Listeners including Printer 
            BoardAgent boardAgent(&board);
            Recorder recorder{};
            board.registerListener(&recorder);
            Printer_OneColor printer(renderer);
            printer.addEndPoint(N1.first, N1.second);
            printer.addEndPoint(E2.first, E2.second);
            printer.addEndPoint(E3.first, E3.second);
            printer.addEndPoint(S4.first, S4.second);
            printer.addEndPoint(S5.first, S5.second);
            printer.addEndPoint(W6.first, W6.second);
            printer.addEndPoint(W7.first, W7.second);
            recorder.registerListener(&printer);

            // Create decider
            Decider_Safe dec{};

            // Event loop exit flag
            bool running = true;

            vector<unique_ptr<thread>> thread{};
            
            int count = 100;
            int boxId = 0;
            insertThread(thread, Position{350, 11}, Position{450, 11}, &board, pm, dec, boxId, running, count);
            boxId += count;
            insertThread(thread, Position{788, 175}, Position{788, 225}, &board, pm, dec, boxId, running, count);
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
