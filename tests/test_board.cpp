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

    board.addNote(Position{5, 5}, BoardNote{10, 4});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{10, 4});

    board.addNote(Position{5, 5}, BoardNote{10, 1});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{10, 1});

    board.addNote(Position{5, 5}, BoardNote{10, 3});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{-1, -1});
}

TEST_CASE("Sends changes to registered Agents")
{
    class Agent_Test : public Agent
    {
    public: 
        Agent_Test(Board* board):_board{board}{}

        void updateWithChanges() override 
        {
            _board->sendChanges();
        }

        void receiveChanges(unordered_map<Position, int> typePerPosition) override
        {
            for(auto& pairTypePerPosition : typePerPosition)
            {
                _typePerPosition.insert({pairTypePerPosition.first, pairTypePerPosition.second});
            }
        }
        
        Board* _board;        
        unordered_map<Position, int> _typePerPosition{};
    };

    Board board{10, 10};
    Agent_Test agent{&board};
    board.registerAgent(&agent);

    board.addNote(Position{5, 5}, BoardNote{0, 2});
    board.addNote(Position{6, 6}, BoardNote{0, 2});

    agent.updateWithChanges();
    REQUIRE(agent._typePerPosition.size() == 100);
    REQUIRE(2 == agent._typePerPosition[Position{5, 5}]);
    REQUIRE(2 == agent._typePerPosition[Position{6, 6}]);

    agent._typePerPosition.clear();

    board.addNote(Position{5, 5}, BoardNote{0, 4});
    board.addNote(Position{7, 7}, BoardNote{0, 2}); 
    agent.updateWithChanges();
    
    REQUIRE(agent._typePerPosition.size() == 100);
    REQUIRE(4 == agent._typePerPosition[Position{5, 5}]);
    REQUIRE(2 == agent._typePerPosition[Position{7, 7}]);
}
