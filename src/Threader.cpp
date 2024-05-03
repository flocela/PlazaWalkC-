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

    /* Move Box on to @board. */

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


    /* Move Box to final Position */
   
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
        
        // If @decider returned an invalid Position, then sleep for now. Otherwise try to move to nextPosition.
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

void Threader::populateThreads(
    vector<unique_ptr<thread>>& threads,
    int numOfBoxesPerGroup,
    int numOfGroups,
    const vector<Rectangle>& startEndRectangles,
    Board& board,
    bool& running)
{
    // Each thread contains one boxId.
    // Get number of required Boxes per group from numOfBoxesPerGroup. Then create that many threads per group.
    for(int ii=0; ii<numOfGroups; ++ii)
    {
        // PositionManagerType is random.
        PositionManagerType pmType = 
            (Util::getRandomBool()) ? (PositionManagerType::step) : (PositionManagerType::diagonal);

        // DeciderType is random.
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
