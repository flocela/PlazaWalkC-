#include "catch.hpp"
#include "../src/Board.h"

using namespace std;

TEST_CASE("Insert BoardNotes with different types to Position{5, 5}. The getNoteAt() method should return the new BoardNote after each insertion.")
{  
    int boxId = 0;
    vector<Box> boxes(1,Box{0, 0, 1, 1,});
    Board board{20, 10, std::move(boxes)};
    
    board.addNote(Position{5, 5}, BoardNote{boxId, SpotType::to_arrive});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{boxId, SpotType::to_arrive});

    board.addNote(Position{5, 5}, BoardNote{boxId, SpotType::arrive});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{boxId, SpotType::arrive});

    board.addNote(Position{5, 5}, BoardNote{boxId, SpotType::to_leave});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{boxId, SpotType::to_leave});

    board.addNote(Position{5, 5}, BoardNote{boxId, SpotType::left});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{-1, SpotType::left});

}

// When receiveChanges() is called, TempListener 1) receives and saves changes to Spots, 2) receives and then saves BoxInfos. Note, changes to Spots are in fact changes since the last time receivedChanges() was called. The BoxInfos received are the current state of the Boxes. 
class TempListener : public BoardListener 
{
public: 

    void receiveChanges(
        unordered_map<SpotType, unordered_set<Drop>> setsOfDropsPerType,
        unordered_map<int, BoxInfo> boxes) override
    {
        for(const auto& p: boxes)
        {
            _boxes.insert({p.second.getId(), p.second});
        }

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
    unordered_map<int, BoxInfo> _boxes{};
};

TEST_CASE("Verify changes to Board's Spots and that BoardListener receives those changes. Create a BoardListener which saves changes that are sent to it. Make changes to Board. Request that Board send changes to the BoardListener. Verify that the BoardListener received the changes.")
{
    // Create one box with id=0, groupId=0, width=1, height=1.
    vector<Box> boxes(1, Box{0, 0, 1, 1,});

    Board board{10, 10, std::move(boxes)};
    TempListener listener{};
    board.registerListener(&listener);

    board.addNote(Position{5, 5}, BoardNote{0, SpotType::to_arrive});
    board.addNote(Position{6, 6}, BoardNote{0, SpotType::to_arrive});

    board.sendChanges();

    REQUIRE(listener._dropsPerPosition.size() == 2);
    REQUIRE(SpotType::to_arrive == listener._dropsPerPosition.at(Position{5, 5})._type);
    REQUIRE(SpotType::to_arrive == listener._dropsPerPosition.at(Position{6, 6})._type);

    // Clear listener's drops. Again, add BoardNotes to Board, request Board send changes. Verify BoardListener received changes.
    listener._dropsPerPosition.clear();

    board.addNote(Position{5, 5}, BoardNote{0, SpotType::arrive});
    board.addNote(Position{7, 7}, BoardNote{0, SpotType::to_arrive}); 
    board.sendChanges();
    
    REQUIRE(listener._dropsPerPosition.size() == 2);
    REQUIRE(SpotType::arrive == listener._dropsPerPosition.at(Position{5, 5})._type);
    REQUIRE(SpotType::to_arrive == listener._dropsPerPosition.at(Position{7, 7})._type);
}

TEST_CASE("Verify 1) addNotes() returns false when unsuccessful and 2) BoardListener receives changes Boxes. Using the addNote() method, a box with id of 20 attempts to move to position where a box with id 10 is at. Both boxes' levels go up.")
{
    int boxId_0 = 0;
    int boxId_1 = 1;
    
    vector<Box> boxes{Box{boxId_0, 0, 1, 1}, Box{boxId_1, 0, 1, 1}};
    Board board{20, 20, std::move(boxes)};
    
    TempListener listener{};
    board.registerListener(&listener);
  
    board.addNote(Position{5, 5}, BoardNote{boxId_0, SpotType::to_arrive});

    // successful should be false and both boxes' levels go up by 1
    bool successful = board.addNote(Position{5, 5}, BoardNote{boxId_1, SpotType::to_arrive});
    REQUIRE(false == successful);
    
    // successful should be false again, and both boxes' levels go up by 1 again.
    successful = board.addNote(Position{5, 5}, BoardNote{boxId_1, SpotType::to_arrive}); 
    REQUIRE(false == successful);
    board.sendChanges();
   
    REQUIRE(2 == listener._boxes.at(0).getLevel());
    REQUIRE(2 == listener._boxes.at(1).getLevel());
}


TEST_CASE("Adding a BoardNote with an unknown BoxId results in an exception.")
{
    int boxId_0 = 0;
    int boxId_1 = 1;
    
    vector<Box> boxes{Box{boxId_0, 0, 1, 1}, Box{boxId_1, 0, 1, 1}};
    Board board{20, 20, std::move(boxes)};

    // Board does not have a Box id of 100.
    REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{100, SpotType::to_arrive}));
}

