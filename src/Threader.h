#ifndef THREADER__H
#define THREADER__H

#include <memory>
#include <thread>
#include "Board.h"
#include "Mover.h"
#include "Position.h"
#include "PositionManager.h"
#include "Decider.h"

class Threader
{
public:
    void  PMSlideAndSafeDecider(
        std::vector<std::unique_ptr<std::thread>>& threads,
        Position topLeftCornerOfStartPoint,
        Position bottomRightCornerOfStartPoint,
        std::vector<std::pair<Position, Position>> endRanges,
        Board& board,
        int firstBoxId,
        int count,
        bool& running); 

    static void funcMoveBox(
            Position position,
            Board& board,
            std::unique_ptr<PositionManager> posManager,
            std::unique_ptr<Decider> decider,
            std::unique_ptr<Mover> mover,
            bool& breaker);

    //TODO test and put in a utility class
    static std::vector<int>  getRandom(int start, int end, int count);

    // TODO test and put in a utility class
    static std::vector<Position>  getRandomOnLine(Position a, Position b, int count);

    // TODO test and put in a utility class
    static std::vector<Position> getRandomInRectangle(Position a, Position b, int count);

    static void testFunc(Position position, Board& board, std::unique_ptr<PositionManager> pm, std::unique_ptr<Decider> decider, std::unique_ptr<Mover> mover, bool& breaker){
        (void)position;
        (void)board;
        (void)pm;
        (void)decider;
        (void)mover;
        (void)breaker;
        getRandom(0, 0, 0);
    }
    static void func(Board& board){
    (void)board;
    }
        
};
#endif
