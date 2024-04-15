#include "Threader.h"

#include <chrono>
#include "Decider_Risk1.h"
#include "Decider_Safe.h"
#include "Mover_Reg.h"
#include "PositionManager_Slide.h"
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
        if(decider->addToBoard(position, board))
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
        pair<Position,int> nextPosition = decider->getNextPosition(
                                            posManager->getFuturePositions(curPosition),
                                            board);
        if (nextPosition.first != Position{-1, -1})
        {  
            if (nextPosition.second != 0)
            {
               this_thread::sleep_for(chrono::milliseconds(nextPosition.second));
            } 
            if (mover->moveBox(curPosition, nextPosition.first))
            {
                curPosition = nextPosition.first;
            }
        }
        this_thread::sleep_for(10ms);
    }

    // if box has reached its destination then it disapears from the board.
    if (posManager->atEnd(curPosition))
    {
        mover->removeBox(curPosition);
    }
}

void Threader::PMSlideAndSafeDecider(
    std::vector<unique_ptr<thread>>& threads,
    Position topLeftCornerOfStartPoint,
    Position bottomRightCornerOfStartPoint,
    std::vector<std::pair<Position, Position>> endRanges, // these are rectangles
    Board& board,
    int firstBoxId,
    int count,
    bool& running)

{
    int erSize = endRanges.size();
    vector<Position> startPoints = 
        Util::getRandomInRectangle(topLeftCornerOfStartPoint, bottomRightCornerOfStartPoint, count);

    vector<vector<Position>> endPositionPerEndRange{};

    for(int ii=0; ii<erSize; ++ii)
    {
        int countPerRange = (count/erSize) + 1;
        endPositionPerEndRange.push_back(
            Util::getRandomInRectangle(endRanges[ii].first, endRanges[ii].second, countPerRange));
    };

    for(int ii=0; ii<count; ++ii)
    {
        threads.push_back(make_unique<thread>(
            funcMoveBox,
            startPoints[ii],
            std::ref(board),
            make_unique<PositionManager_Slide>(
                endPositionPerEndRange[ii%erSize][ii/erSize],
                0,
                board.getWidth()-1,
                0,
                board.getHeight()-1),
            make_unique<Decider_Risk1>(),
            make_unique<Mover_Reg>(firstBoxId+ii, &board),
            std::ref(running)
        )
        );
    }
} 

