#ifndef THREADER__H
#define THREADER__H

#include <memory>
#include <thread>
#include "Board.h"
#include "DeciderType.h"
#include "Mover.h"
#include "Position.h"
#include "PositionManager.h"
#include "PositionManagerType.h"
#include "Decider.h"

class Threader
{
public:
    void populateThreads(
        std::vector<std::unique_ptr<std::thread>>& threads,
        Position topLeftCornerOfStartPoint,
        Position bottomRightCornerOfStartPoint,
        std::vector<std::pair<Position, Position>> endRanges,
        Board& board,
        int firstBoxId,
        int count,
        PositionManagerType pmt,
        DeciderType dt,
        bool& running);

    void populateRandomPoints(
        std::vector<Position>& randomPositions,
        std::vector<std::pair<Position, Position>> rects,
        int numOfPoints);

    std::unique_ptr<PositionManager> createPositionManager(
        PositionManagerType pmt,
        Position endPoint,
        int boardMinX,
        int boardMaxX,
        int boardMinY,
        int boardMaxY);

    std::unique_ptr<Decider> createDecider(DeciderType dt);

    void populateThreads_Slide_Safe(
        std::vector<std::unique_ptr<std::thread>>& threads,
        Position topLeftCornerOfStartPoint,
        Position bottomRightCornerOfStartPoint,
        std::vector<std::pair<Position, Position>> endRanges,
        Board& board,
        int firstBoxId,
        int count,
        bool& running); 
   /* 
    void populateThreads_Slide_Risky1(
        std::vector<std::unique_ptr<std::thread>>& threads,
        Position topLeftCornerOfStartPoint,
        Position bottomRightCornerOfStartPoint,
        std::vector<std::pair<Position, Position>> endRanges,
        Board& board,
        int firstBoxId,
        int count,
        bool& running); 
    
    void populateThreads_Direct_Safe(
        std::vector<std::unique_ptr<std::thread>>& threads,
        Position topLeftCornerOfStartPoint,
        Position bottomRightCornerOfStartPoint,
        std::vector<std::pair<Position, Position>> endRanges,
        Board& board,
        int firstBoxId,
        int count,
        bool& running); 
*/
    static void funcMoveBox(
        Position position,
        Board& board,
        std::unique_ptr<PositionManager> posManager,
        std::unique_ptr<Decider> decider,
        std::unique_ptr<Mover> mover,
        bool& breaker);

};
#endif
