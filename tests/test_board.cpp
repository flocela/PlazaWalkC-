#include "catch.hpp"
#include "../src/Board.h"
#include <thread>

using namespace std;

TEST_CASE("getHeight() and getWidth() return the Board's dimensions")
{
    Board board{20, 10};
    REQUIRE(board.getHeight() == 10);
    REQUIRE(board.getWidth() == 20); 
}

TEST_CASE("Add BoardNotes with different types to Position{5, 5}. The retrieved boardnotes' types should reflect the newly given boardnotes.")
{  
    int boxId = 10; 
    Board board{20, 10};
    
    // BoardNote(int type, int boxId)
    board.addNote(Position{5, 5}, BoardNote{boxId, 2});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{boxId, 2});

    board.addNote(Position{5, 5}, BoardNote{boxId, 4});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{boxId, 4});

    board.addNote(Position{5, 5}, BoardNote{boxId, 1});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{boxId, 1});

    board.addNote(Position{5, 5}, BoardNote{boxId, 3});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{-1, -1});

}

TEST_CASE("Sends changes to registered Agents")
{
    class BoardListener_Test : public BoardListener 
    {
    public: 

        void receiveChanges(std::unordered_map<int, unordered_set<Drop>> setsOfDropsPerType) override
        {
            for(auto& setOfDropsPerType : setsOfDropsPerType)
            {
                int type = setOfDropsPerType.first;

                for (auto& drop : setOfDropsPerType.second)
                {
                    _dropsPerPosition.insert({drop._position, drop});
                }
            }
        }
        
        unordered_map<Position, Drop> _dropsPerPosition{};
    };

    Board board{10, 10};
    BoardListener_Test listener{};

    board.registerListener(&listener);

    board.addNote(Position{5, 5}, BoardNote{0, 2});
    board.addNote(Position{6, 6}, BoardNote{0, 2});

    board.sendChanges();
    REQUIRE(listener._dropsPerPosition.size() == 2);
    REQUIRE(2 == listener._dropsPerPosition.at(Position{5, 5})._type);
    REQUIRE(2 == listener._dropsPerPosition.at(Position{6, 6})._type);

    listener._dropsPerPosition.clear();

    board.addNote(Position{5, 5}, BoardNote{0, 4});
    board.addNote(Position{7, 7}, BoardNote{0, 2}); 
    board.sendChanges();
    
    REQUIRE(listener._dropsPerPosition.size() == 2);
    REQUIRE(4 == listener._dropsPerPosition.at(Position{5, 5})._type);
    REQUIRE(2 == listener._dropsPerPosition.at(Position{7, 7})._type);
}

void funcMoveBox(Board& board)
{
    for (int ii=0; ii<1000; ++ii)
    {
         board.addNote(Position{ii, 0}, BoardNote{ii*1000, 2});
    }
}

void funcAskForChanges(Board& board)
{
    for (int ii=0; ii<1000; ++ii)
    {
        board.sendChanges();
    }
}
        
// In order to fail this test: remove the unique_lock in sendChanges() and add a this_thread::sleep_for(1ms) in addNote (after drop._boxId has been updated, but before drop._type has been updated).
TEST_CASE("removing the unique_lock protecting _receivingMatrix results in Drops that have a boxId of -1 and type of not -1.")
{

    // If the unique_lock protrecting _receivingMatrix is removed, then a Drop in say dropMatrix1 will receive the change to it's _boxId, but the corresponding Drop in dropMatrix2 will receive the change to its _type.
    class BoardListener_Test : public BoardListener 
    {
    public: 

        void receiveChanges(std::unordered_map<int, unordered_set<Drop>> setsOfDropsPerType) override
        {
            for(auto& setOfDropsPerType : setsOfDropsPerType)
            {
                int type = setOfDropsPerType.first;

                for (auto& drop : setOfDropsPerType.second)
                {
                    if (type == -1)
                    {
                            REQUIRE(drop._boxId == -1);
                    } 
                    if (type != -1)
                    {
                            REQUIRE(drop._boxId != -1);
                    }
                }
            }
        }
        
    };

    Board board{1000, 1000};
    BoardListener_Test listener{};
    board.registerListener(&listener);

    std::thread t1(funcMoveBox, std::ref(board));
    std::thread t2(funcAskForChanges, std::ref(board));

    t1.join();
    t2.join();

}
