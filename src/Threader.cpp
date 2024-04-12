#include "Threader.h"

#include <random>
#include "Decider_Safe.h"
#include "Mover_Reg.h"
#include "PositionManager_Slide.h"

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
    while(!mover->addBox(curPosition) && breaker)
    {
        this_thread::sleep_for(n * 10ms);
        ++n;
    }

    while (!posManager->atEnd(curPosition) && breaker)
    {
        Position nextPosition = decider->getNextPosition(
                                            posManager->getFuturePositions(curPosition),
                                            board);
        if (nextPosition != Position{-1, -1})
        {
            if (mover->moveBox(curPosition, nextPosition))
            {
                curPosition = nextPosition;
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
        getRandomInRectangle(topLeftCornerOfStartPoint, bottomRightCornerOfStartPoint, count);

    vector<vector<Position>> endPositionPerEndRange{};

    for(int ii=0; ii<erSize; ++ii)
    {
        int countPerRange = (count/erSize) + 1;
        endPositionPerEndRange.push_back(
            getRandomInRectangle(endRanges[ii].first, endRanges[ii].second, countPerRange));
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
            make_unique<Decider_Safe>(),
            make_unique<Mover_Reg>(firstBoxId+ii, &board),
            std::ref(running)
        )
        );
    }

/*

    thread t1(testFunc);

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
            make_unique<Decider_Safe>(),
            make_unique<Mover_Reg>(firstBoxId+ii, &board),
            std::ref(running)));
    }
       */ 
} 

vector<int> Threader::getRandom(int start, int end, int count)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(start, end);
   
    vector<int> randomInts{};
    for(int ii=0; ii<count; ++ii)
    {
        randomInts.push_back(distribution(gen));
    }
    return randomInts;
} 

// TODO test and put in a utility class
vector<Position> Threader::getRandomOnLine(Position a, Position b, int count)
{
    int x1 = a.getX();
    int x2 = b.getX();
    int y1 = a.getY();
    int y2 = b.getY();

    vector<Position> positions{};
    vector<int> randomXs = getRandom(x1, x2, count);
    for(int x3: randomXs)
    {
        int y3 = y1 + ( (x3- x1) * ((y2 - y1)/(x2-x1)) );
        positions.push_back({x3, y3});
    }
    
    return positions;
}

// TODO test and put in a utility class
vector<Position> Threader::getRandomInRectangle(Position a, Position b, int count)
{
    int x1 = a.getX();
    int x2 = b.getX();
    int y1 = a.getY();
    int y2 = b.getY();

    vector<int> randomXs = getRandom(x1, x2, count);
    vector<int> randomYs = getRandom(y1, y2, count);

    vector<Position> positions{};
    for(int ii=0; ii<count; ++ii)
    {
        positions.push_back({randomXs[ii], randomYs[ii]});
    }
    
    return positions;
}
        
