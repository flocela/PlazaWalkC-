#include "Threader.h"

#include <chrono>
#include "Decider_Risk1.h"
#include "Decider_Safe.h"
#include "MainSetup.h"
#include "Mover_Reg.h"
#include "PositionManager_Diagonal.h"
#include "PositionManager_Down.h"
#include "PositionManager_Step.h"
#include "PositionManager_Up.h"
#include "Util.h"

using namespace std;

// Moves Box from @position to final position given in @posManager.
// Assumes Box is not originally on the board.
// First repeatedly tries to add Box to @board at @position.
// Once the Box is on the Board, then continually moves box closer to final position in @posManager.
// Note @breaker is a reference that is checked between Position moves. If false, the function ends.
void Threader::funcMoveBox(
        Position position,
        Board& board,
        unique_ptr<PositionManager> posManager,
        unique_ptr<Decider> decider,
        unique_ptr<Mover> mover,
        bool& breaker
)
{  
    Position curPosition = position;

    // Move Box on to @board. 
    int n = 1;
    while(breaker)
    {
        // See if @decider suggests moving to Position. If not then wait.
        if(decider->suggestMoveTo(position, board))
        {
            if(mover->addBox(curPosition))
            {
                // Move was successful. Box is on the Board.
                break;
            }
        }
        this_thread::sleep_for(n * 10ms);
        ++n;
    }
   
    // While the box is not at the end position, keep moving the box closer. 
    while (!posManager->atEnd(curPosition) && breaker)
    {
        // Get vector of Positions from @posManager.
        // @decider chooses which Position to move to.
        pair<Position,int> nextPosition = 
            decider->getNext(posManager->getFuturePositions(curPosition),
                                     board);
        // If suggested sleep time from @decider is positive, then sleep for suggested sleep time.
        if(nextPosition.second > 0)
        {
           this_thread::sleep_for(chrono::milliseconds(nextPosition.second));
        }
        
        // @decider may return an invalid Position, signaling to simply sleep for now.
        if((nextPosition.first != Position{-1, -1}) && 
           (mover->moveBox(curPosition, nextPosition.first)))
        {
            // Move was successful. Update curPosition.
            curPosition = nextPosition.first;
        }
        // Always sleep between movements.
        this_thread::sleep_for(10ms);
    }

    if(!breaker)
    {
        return;
    }

    // If box has reached its final destination then it disapears from the Board.
    if (posManager->atEnd(curPosition))
    {
        mover->removeBox(curPosition);
    }
}

// Creates threads using funcMoveBox() and places them in @threads. Each thread represents a Box moving on @board.  There will be @count Boxes starting at firstBoxId.
// All Boxes start at a random point inside of the rectangle created from tlStartPoint and brStartPoint
// A PositionManager is created for each thread based on @pmt.
// A random endpoint is given to the PositionManager. The endpoint is made by randomly selecting a rectangle in @endRects and then randomly choosing a point in that rectangle.
// The thread is given @dt so it can make decisions on whether it should move and which Position to choose from the positions given by the PositionManager.
// A breaking reference @running is checked between Position moves. If it is false, the thread returns.
void Threader::populateThreadsForOneGroup(
    vector<unique_ptr<thread>>& threads,
    int firstBoxId,
    int count,
    Rectangle startRectangle,
    vector<Rectangle> endRects, 
    Board& board,
    PositionManagerType pmt,
    DeciderType dt,
    bool& running)

{
    vector<Position> startPoints = Util::getRandomPositionsInRectangle(
        startRectangle,
        count);

    for(int ii=0; ii<count; ++ii)
    {
        threads.push_back(
            make_unique<thread>(
                funcMoveBox,
                startPoints[ii],
                std::ref(board),
                createPositionManager(pmt,
                                      endRects[Util::getRandomInt(0, endRects.size()-1)],
                                      0,
                                      board.getWidth()-1,
                                      0,
                                      board.getHeight()-1),
                createDecider(dt),
                make_unique<Mover_Reg>(firstBoxId+ii, &board),
                std::ref(running))
        );
    }
} 

// Creates threads using funcMoveBox() and places them in @threads. Each thread represents a Box moving on @board.
// The maps @boxIdsAndCountsPerGroup, @rectsPerGroup, and @pmtsPerGroup must all have the same number of items. Thread information from each of the maps is used to make each of the groups of threads.
// Each pair of ints in @boxIdsAndCountsPerGroup represents the first boxId of the group(pair's first int) and the number of boxes in the group (second int).
// Each rectangle in @rectsPerGroup represents the starting rectangle for the group. The rest of the rectangles in @rectsPerGroup represent the group's end rectangles.
void Threader::populateThreads(
    vector<unique_ptr<thread>>& threads,
    int numOfBoxesPerGroup,
    int numOfGroups,
    const vector<Rectangle>& startEndRectangles,
    Board& board,
    bool& running)
{
    for(int ii=0; ii<numOfGroups; ++ii)
    {
        PositionManagerType pmType = 
            (Util::getRandomBool()) ? (PositionManagerType::step) : (PositionManagerType::diagonal);
        DeciderType dType = (Util::getRandomBool()) ? (DeciderType::safe) : (DeciderType::risk1);
        populateThreadsForOneGroup(
            threads,
            ii*numOfBoxesPerGroup,
            numOfBoxesPerGroup,
            startEndRectangles[ii],
            MainSetup::deleteRect(startEndRectangles, startEndRectangles[ii]),
            board,
            pmType,
            dType,
            running);
    }
}

// Adds Positions from the rectangles in @rects to @randomPositions.
// The number of Positions that are added from each rectangle is @numOfPointsFromEachRectangle.
// The Positions are chosen radomly from inside each rectangle.
// The Positions are shuffled in @randomPositions. Taking an index in @randomPosition, which rectangle it comes from in @rects is random.
void Threader::populateRandomPoints(
    vector<Position>& randomPositions,
    vector<Rectangle> rects,
    int numOfPointsFromEachRect)
{
    for(size_t ii=0; ii<rects.size(); ++ii)
    {
        // vector of random positions to append to randomPositions.
        vector<Position> toAppend = Util::getRandomPositionsInRectangle(
            rects[ii],
            numOfPointsFromEachRect);

        randomPositions.insert(randomPositions.end(), toAppend.begin(), toAppend.end());
    };

    Util::utilShuffle(randomPositions);
}

unique_ptr<PositionManager> Threader::createPositionManager(
    PositionManagerType pmt,
    Rectangle endRectangle,
    int boardMinX,
    int boardMaxX,
    int boardMinY,
    int boardMaxY)
{
    if(pmt == PositionManagerType::diagonal)
    {
        Position randomP = Util::getRandomPositionInRectangle(endRectangle);
        return make_unique<PositionManager_Diagonal>(
            endRectangle,
            randomP,
            boardMinX,
            boardMaxX,
            boardMinY,
            boardMaxY);
    }
    else if (pmt == PositionManagerType::down)
    {
        int minY = std::min(endRectangle.getTopLeft().getY(), endRectangle.getBottomRight().getY());
        int maxY = std::max(endRectangle.getTopLeft().getY(), endRectangle.getBottomRight().getY());
        return make_unique<PositionManager_Down>(
            minY + ((maxY - minY)/2),
            boardMinX,
            boardMaxX,
            boardMinY,
            boardMaxY);
    }
    else if (pmt == PositionManagerType::up)
    {
        int minY = std::min(endRectangle.getTopLeft().getY(), endRectangle.getBottomRight().getY());
        int maxY = std::max(endRectangle.getTopLeft().getY(), endRectangle.getBottomRight().getY());
        return make_unique<PositionManager_Up>(
            minY + ((maxY - minY)/2),
            boardMinX,
            boardMaxX,
            boardMinY,
            boardMaxY);
    }
    else
    {
        return make_unique<PositionManager_Step>(
            Util::getRandomPositionInRectangle(endRectangle),
            boardMinX,
            boardMaxX,
            boardMinY,
            boardMaxY);
    }
}
    
unique_ptr<Decider> Threader::createDecider(DeciderType dt)
{
    if(dt == DeciderType::risk1)
    {
        return make_unique<Decider_Risk1>();
    }
    else
    {
        return make_unique<Decider_Safe>();
    }
} 
