#include "catch.hpp"
#include "../src/Board.h"
#include <thread>

using namespace std;

void funcMoveBoxToPosition(Board& board, int id, Position pos, int times)
{
    for (int ii=0; ii<times; ++ii)
    {
         board.addNote(pos, BoardNote{id, SpotType::to_arrive});
    }
}

void funcAskForChanges(Board& board, int times)
{
    for (int ii=0; ii<times; ++ii)
    {
        board.sendChanges();
    }
}

// To make this fail move the "copy _boxes to send" for loop in the sendChanges() function outside the unique_lock lockUq's braces.
TEST_CASE("Box with id of 20 repeatedly attempts to move to position where box with id of 10 is at. Both boxes' levels are always the same.")
{
    class BoardListener_Test : public BoardListener 
    {
    public: 

        void receiveChanges(unordered_map<SpotType, unordered_set<Drop>> setsOfDropsPerType, unordered_map<int, BoxInfo> boxes) override
        {
            try{
                REQUIRE(boxes.at(0).getLevel() == boxes.at(1).getLevel());
            }
            catch(...)
            {
                return;
            }
        }
        
    };

    int boxId0 = 0;
    int boxId1 = 1;
    
    vector<Box> boxes{Box{0, 0, 1, 1}, Box{1, 0, 1, 1}};
    Board board{20, 20, std::move(boxes)};
    BoardListener_Test listener{};
    board.registerListener(&listener);
  
    board.addNote(Position{5, 5}, BoardNote{boxId0, SpotType::to_arrive});

    std::thread t1(funcMoveBoxToPosition, std::ref(board), boxId1, Position{5, 5}, 100);
    std::thread t2(funcAskForChanges, std::ref(board), 100);

    t1.join();
    t2.join();
    
}

void funcMoveBox(Board& board)
{
    for (int ii=0; ii<1000; ++ii)
    {
         board.addNote(Position{ii, 0}, BoardNote{ii, SpotType::to_arrive});
    }
}
        
// In order to fail this test: remove the unique_lock in sendChanges() and add a this_thread::sleep_for(1ms) in addNote (after drop._boxId has been updated, but before drop._type has been updated).
TEST_CASE("removing the unique_lock protecting _receivingMatrix results in Drops that have a boxId of -1 and type of not -1.")
{

    // If the unique_lock protrecting _receivingMatrix is removed, then a Drop in say dropMatrix1 will receive the change to it's _boxId, but the corresponding Drop in dropMatrix2 will receive the change to its _type.
    class BoardListener_Test : public BoardListener 
    {
    public: 

        void receiveChanges(std::unordered_map<SpotType, unordered_set<Drop>> setsOfDropsPerType, std::unordered_map<int, BoxInfo> boxes) override
        {
            for(auto& setOfDropsPerType : setsOfDropsPerType)
            {
                SpotType type = setOfDropsPerType.first;

                for (auto& drop : setOfDropsPerType.second)
                {
                    if (type == SpotType::left)
                    {
                            REQUIRE(drop._boxId == -1);
                    } 
                    if (type != SpotType::left)
                    {
                            REQUIRE(drop._boxId != -1);
                    }
                }
            }
        }
        
    };

    vector<Box> boxes{};
    for(int ii=0; ii<1000; ++ii)
    {
        boxes.push_back(Box{ii, 0, 1, 1});
    }

    Board board{1000, 1000, std::move(boxes)};
    BoardListener_Test listener{};
    board.registerListener(&listener);

    std::thread t1(funcMoveBox, std::ref(board));
    std::thread t2(funcAskForChanges, std::ref(board), 1000);

    t1.join();
    t2.join();

}
