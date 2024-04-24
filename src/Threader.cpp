#include "Threader.h"

#include <chrono>
#include "Decider_Risk1.h"
#include "Decider_Safe.h"
#include "MainSetup.h"
#include "Mover_Reg.h"
#include "PositionManager_Step.h"
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
    // TODO what to do if box isn't successfully added to the board?
    int n = 1;

    while(breaker)
    {
        if(decider->suggestMoveTo(position, board))
        {
            if(mover->addBox(curPosition))
            {
                break;
            }
        }
        this_thread::sleep_for(n * 10ms);
        ++n;
    }
    
    while (!posManager->atEnd(curPosition) && breaker)
    {
        pair<Position,int> nextPosition = 
            decider->getNext(posManager->getFuturePositions(curPosition),
                                     board);
        // if suggested sleep time from decider is positive, then sleep for suggested sleep time.
        if(nextPosition.second > 0)
        {
           this_thread::sleep_for(chrono::milliseconds(nextPosition.second));
        }
        // if moving to valid position, sleep for time suggested by decider. 
        if((nextPosition.first != Position{-1, -1}) && 
           (mover->moveBox(curPosition, nextPosition.first)))
        {
            curPosition = nextPosition.first;
        }
        // always sleep between movements.
        this_thread::sleep_for(10ms);
    }

    // if box has reached its final destination then it disapears from the board.
    if (posManager->atEnd(curPosition))
    {
        mover->removeBox(curPosition);
    }
}

void Threader::populateThreadsForOneGroup(
    vector<unique_ptr<thread>>& threads,
    // top left corner of start rectangle
    Position tlStartPoint,
    // bottom right corner of start rectangle
    Position brStartPoint,
    vector<pair<Position, Position>> endRects, 
    Board& board,
    int firstBoxId,
    int count,
    PositionManagerType pmt,
    DeciderType dt,
    bool& running)

{
    vector<Position> startPoints = Util::getRandomInRectangle(tlStartPoint, brStartPoint, count);
    
    // Each rectangle in endRects contributes the same number of points to randomEndPoints.
    int numOfEndPointsPerOneEndRect = (count/endRects.size()) + 1;
    vector<Position> randomEndPoints{};
    populateRandomPoints(randomEndPoints, endRects, numOfEndPointsPerOneEndRect);

    for(int ii=0; ii<count; ++ii)
    {
        threads.push_back(
            make_unique<thread>(
                funcMoveBox,
                startPoints[ii],
                std::ref(board),
                createPositionManager(pmt,
                                      randomEndPoints[ii],
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
    std::vector<std::unique_ptr<std::thread>>& threads,
    std::vector<std::pair<Position, Position>> startPoints,
    std::vector<std::pair<Position, Position>> endRanges,
    Board& board,
    vector<std::pair<int, int>> boxIds,
    std::vector<PositionManagerType> pmts,
    std::vector<DeciderType> dts,
    bool& running)
{
    for(size_t ii=0; ii<startPoints.size(); ++ii)
    {
        populateThreadsForOneGroup(
            threads,
            startPoints[ii].first,
            startPoints[ii].second,
            MainSetup::deleteRect(endRanges, endRanges[ii]),
            board,
            boxIds[ii].first,
            boxIds[ii].second - boxIds[ii].first + 1,
            pmts[ii],
            dts[ii],
            running);
    }
}

void Threader::populateRandomPoints(
    vector<Position>& randomPositions,
    vector<pair<Position, Position>> rects,
    int numOfPoints)
{
    for(size_t ii=0; ii<rects.size(); ++ii)
    {
        // vector of random positions to append to randomPositions.
        vector<Position> toAppend = Util::getRandomInRectangle(
            rects[ii].first,
            rects[ii].second,
            numOfPoints);

        randomPositions.insert(randomPositions.end(), toAppend.begin(), toAppend.end());
    };

    Util::utilShuffle(randomPositions);
}

unique_ptr<PositionManager> Threader::createPositionManager(
    PositionManagerType pmt,
    Position endPoint,
    int boardMinX,
    int boardMaxX,
    int boardMinY,
    int boardMaxY)
{
    if(pmt == PositionManagerType::slide)
    {
        return make_unique<PositionManager_Step>(
            endPoint,
            boardMinX,
            boardMaxX,
            boardMinY,
            boardMaxY);
    }
    else
    {
        return make_unique<PositionManager_Step>(
            endPoint,
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
