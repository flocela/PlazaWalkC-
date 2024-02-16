#include "catch.hpp"
#include "../src/Board.h"

using namespace std;

TEST_CASE("getHeight() and getWidth() return the Board's dimensions")
{
    Board board{20, 10};
    REQUIRE(board.getHeight() == 10);
    REQUIRE(board.getWidth() == 20); 
}

TEST_CASE("Add BoardNotes with different types to Position{5, 5}. The retrieved boardnotes' types should reflect the newly given boardnotes.")
{   
    Board board{20, 10};
    
    // BoardNote(int type, int boxId)
    board.addNote(Position{5, 5}, BoardNote{10, 2});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{10, 2});
    cout << "test_board line 20" << endl;
/*
    board.addNote(Position{5, 5}, BoardNote{10, 4});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{10, 4});

    board.addNote(Position{5, 5}, BoardNote{10, 1});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{10, 1});

    board.addNote(Position{5, 5}, BoardNote{10, 3});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{-1, -1});
*/
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
    //REQUIRE(2 == listener._dropsPerPosition[Position{6, 6}]._type);

    listener._dropsPerPosition.clear();

    board.addNote(Position{5, 5}, BoardNote{0, 4});
    board.addNote(Position{7, 7}, BoardNote{0, 2}); 
    board.sendChanges();
    
    REQUIRE(listener._dropsPerPosition.size() == 2);
    //REQUIRE(4 == listener._dropsPerPosition[Position{5, 5}]._type);
    //REQUIRE(2 == listener._dropsPerPosition[Position{7, 7}]._type);
}
