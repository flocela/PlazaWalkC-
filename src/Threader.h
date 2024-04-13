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

};
#endif
