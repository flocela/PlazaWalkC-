#include "catch.hpp"
#include "../src/Board.h"
#include <thread>

using namespace std;
/*
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
    board.addNote(Position{5, 5}, BoardNote{boxId, SpotType::to_arrive});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{boxId, SpotType::to_arrive});

    board.addNote(Position{5, 5}, BoardNote{boxId, SpotType::arrive});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{boxId, SpotType::arrive});

    board.addNote(Position{5, 5}, BoardNote{boxId, SpotType::to_leave});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{boxId, SpotType::to_leave});

    board.addNote(Position{5, 5}, BoardNote{boxId, SpotType::left});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{-1, SpotType::left});

}

TEST_CASE("Sends changes to registered Agents")
{
    class BoardListener_Test : public BoardListener 
    {
    public: 

        void receiveChanges(std::unordered_map<SpotType, unordered_set<Drop>> setsOfDropsPerType, std::unordered_map<int, Box> boxesPerBoxId) override
        {
            for(auto& setOfDropsPerType : setsOfDropsPerType)
            {
                SpotType type = setOfDropsPerType.first;

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

    board.addNote(Position{5, 5}, BoardNote{0, SpotType::to_arrive});
    board.addNote(Position{6, 6}, BoardNote{0, SpotType::to_arrive});

    board.sendChanges();
    REQUIRE(listener._dropsPerPosition.size() == 2);
    REQUIRE(SpotType::to_arrive == listener._dropsPerPosition.at(Position{5, 5})._type);
    REQUIRE(SpotType::to_arrive == listener._dropsPerPosition.at(Position{6, 6})._type);

    listener._dropsPerPosition.clear();

    board.addNote(Position{5, 5}, BoardNote{0, SpotType::arrive});
    board.addNote(Position{7, 7}, BoardNote{0, SpotType::to_arrive}); 
    board.sendChanges();
    
    REQUIRE(listener._dropsPerPosition.size() == 2);
    REQUIRE(SpotType::arrive == listener._dropsPerPosition.at(Position{5, 5})._type);
    REQUIRE(SpotType::to_arrive == listener._dropsPerPosition.at(Position{7, 7})._type);
}
*/
TEST_CASE("One box tries to enter the position of another box. So both box's levels go up by 1.")
{
    cout << "test_board  line 82" << endl;
    class BoardListener_Test : public BoardListener 
    {
    public: 

        void receiveChanges(std::unordered_map<SpotType, unordered_set<Drop>> setsOfDropsPerType, std::unordered_map<int, Box> boxesPerBoxId) override
        {
            for(const pair<int, Box>& p : boxesPerBoxId)
            {
                _boxesPerBoxId.insert({p.first, p.second});
            }
        }
        
        unordered_map<int, Box> _boxesPerBoxId{};
    };

    int boxId10 = 10;
    int boxId20 = 20;
    
    Board board{20, 20};
    BoardListener_Test listener{};
    board.registerListener(&listener);
    
    board.addNote(Position{5, 5}, BoardNote{boxId10, SpotType::to_arrive});
    board.addNote(Position{5, 5}, BoardNote{boxId20, SpotType::to_arrive});
    board.sendChanges(); 
    
    REQUIRE(1 == listener._boxesPerBoxId.at(boxId10).getLevel());
    REQUIRE(1 == listener._boxesPerBoxId.at(boxId20).getLevel());

    listener._boxesPerBoxId = unordered_map<int,Box>{};

    board.addNote(Position{5, 5}, BoardNote{boxId10, SpotType::arrive});
    board.addNote(Position{5, 5}, BoardNote{boxId20, SpotType::to_arrive});
    board.sendChanges(); 
    
    REQUIRE(2 == listener._boxesPerBoxId.at(boxId10).getLevel());
    REQUIRE(2 == listener._boxesPerBoxId.at(boxId20).getLevel());
    
    listener._boxesPerBoxId = unordered_map<int,Box>{};

    board.addNote(Position{5, 5}, BoardNote{boxId10, SpotType::to_leave});
    board.addNote(Position{5, 5}, BoardNote{boxId20, SpotType::to_arrive});
    board.sendChanges(); 
    
    REQUIRE(3 == listener._boxesPerBoxId.at(boxId10).getLevel());
    REQUIRE(3 == listener._boxesPerBoxId.at(boxId20).getLevel());
    
    listener._boxesPerBoxId = unordered_map<int,Box>{};

    board.addNote(Position{5, 5}, BoardNote{boxId10, SpotType::left});
    board.addNote(Position{5, 5}, BoardNote{boxId20, SpotType::to_arrive});
    board.sendChanges(); 
    
    REQUIRE(3 == listener._boxesPerBoxId.at(boxId10).getLevel());
    REQUIRE(3 == listener._boxesPerBoxId.at(boxId20).getLevel());
}

    
/*
void funcMoveBox(Board& board)
{
    for (int ii=0; ii<1000; ++ii)
    {
         board.addNote(Position{ii, 0}, BoardNote{ii*1000, SpotType::to_arrive});
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

        void receiveChanges(std::unordered_map<SpotType, unordered_set<Drop>> setsOfDropsPerType, unordered_map<int, Box> boxesPerBoxId) override
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

    Board board{1000, 1000};
    BoardListener_Test listener{};
    board.registerListener(&listener);

    std::thread t1(funcMoveBox, std::ref(board));
    std::thread t2(funcAskForChanges, std::ref(board));

    t1.join();
    t2.join();

}

*/    
