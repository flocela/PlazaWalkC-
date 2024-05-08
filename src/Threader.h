#ifndef THREADER__H
#define THREADER__H

#include <thread>
#include "Board.h"
#include "Decider.h"
#include "DeciderType.h"
#include "Mover.h"
#include "Position.h"
#include "PositionManager.h"
#include "PositionManagerType.h"
#include "Rectangle.h"

class Threader
{
    public:

    /*
    Moves Box from @position to the final position given in @posManager.
    Assumes Box is not originally on the Board.
    First repeatedly tries to add Box to @board at @position.
    Once the Box is on the Board, then continually moves box closer to target position in @posManager.
    Note @breaker is a reference that is checked between Position moves. If false, the function ends.
    */
    static void funcMoveBox(
        Position position,
        Board& board,
        std::unique_ptr<PositionManager> posManager,
        std::unique_ptr<Decider> decider,
        std::unique_ptr<Mover> mover,
        bool& breaker);


    /*
    Creates threads using the funcMoveBox() method and places them into @threads. Each thread represents a Box moving on @board. There will be @count Boxes and their boxIds start at @firstBoxId.
    
    All Boxes start at a random point inside of @startRect.

    A PositionManager is created for each thread based on @pmt. A PositionManager suggests Positions for the Box to move to given the Box's final destination. 

    A random endpoint is given to the PositionManager. The endpoint is made by randomly selecting a rectangle in the @endRects vector and then randomly choosing a point in that Rectangle.

    A Decider is created based on @dt. The Decider gives suggestions as to which Position the Box should choose to move to, and whether to move to that Position at all.

    A breaking reference @running is checked between Position moves. If it is false, the thread returns.
    */
    void populateOneBatchOfThreads(
        std::vector<std::unique_ptr<std::thread>>& threads,
        int firstBoxId,
        int count,
        Rectangle startRect,
        std::vector<Rectangle> inOutBoundRects,
        Board& board,
        PositionManagerType pmt,
        DeciderType dt,
        bool& running);


    /* Creates batches of threads using funcMoveBox() and places those threads into @threads. Each thread represents a Box moving on @board.

    The number of threads per batch is @numOfBoxesPerBatch; each thread has one boxId.

    Number of threads created is @numOfBoxesPerBatch x @numOfBatches.

    The PositionManagerType is randomly chosen between PositionManagerType::step and PositionManagerType::diagonal. The DeciderType is randomly chosen between DeciderType::risk1 and DeciderType::safe.

    There are an equal number of Boxes starting at each in-out-bound Rectangle. The final target of each box is taken by randomly choosing an out-bound Rectangle from @inOutBoundRects (can't choose the same target Rectangle as starting Rectangle), then choosing a random Position inside the out-bound Rectangle.
    */
    void populateThreads(
        std::vector<std::unique_ptr<std::thread>>& threads,
        int numOfBoxesPerBatch,
        int numOfBatches,
        const std::vector<Rectangle>& startEndRectangles,
        Board& board,
        bool& running);


    /*
    Creates a PositionManager based on @pmt.

    The final target is chosen from @endRectangle. The PositionManager is chosen based on @pmt. If a PositionManager_Diagonal or PositionManager_Step is chosen, then it's final target Position is randomly chosen from inside @endRectangle. If a PositionManager_Up or PositionManager_Down is chosen, then the finalY is taken at the center of @endRectangle.
    */
    std::unique_ptr<PositionManager> createPositionManager(
        PositionManagerType pmt,
        Rectangle endRectangle,
        int boardMinX,
        int boardMaxX,
        int boardMinY,
        int boardMaxY);


    /*
    Creates a Decider based on @dt.
    */
    std::unique_ptr<Decider> createDecider(DeciderType dt);

};
#endif
