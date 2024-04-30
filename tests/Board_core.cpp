#include "catch.hpp"
#include "../src/Board.h"

using namespace std;

TEST_CASE("Board_core::")
{
    SECTION("Insert BoardNotes with different types to Position{5, 5}. The getNoteAt() method should return the new BoardNote after each insertion.")
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

    /* 
    TempListener is a BoardListener that saves the last drops and boxes that were received in the last call to receiveChanges().
    When receiveChanges() is called, TempListener 1) receives and saves changes to Spots, 2) receives and saves the BoxInfos. Note, changes to Spots are in fact changes since the last time receivedChanges() was called. The BoxInfos received are the current state of the Boxes.
    */
    class TempListener : public BoardListener 
    {
        public: 

        void receiveChanges(
            unordered_set<Drop> drops,
            unordered_map<int, BoxInfo> boxes) override
        {
            _dropsPerPosition.clear();
            _boxes.clear();
            for(const auto& p: boxes)
            {
                _boxes.insert({p.second.getId(), p.second});
            }

            for(auto& drop : drops)
            {
                _dropsPerPosition.insert({drop.getPosition(), drop});
            }
        }
        
        unordered_map<Position, Drop> _dropsPerPosition{};
        unordered_map<int, BoxInfo> _boxes{};
    };

    SECTION("Verify changes to Board's Spots are sent to the BoardListener. Use TempListener which saves the changed Spots and state of the Boxes it receives. Make changes to Board. Request that Board send changes to the BoardListener. Verify that the BoardListener received the changes.")
    {
        // Create boxes with id=0, id=1, and id=2.
        vector<Box> boxes{Box{0, 0, 5, 5}, Box{1, 1, 5, 5}, Box{2, 2, 5, 5}};

        Board board{10, 10, std::move(boxes)};
        TempListener listener{};
        board.registerListener(&listener);

        board.addNote(Position{5, 5}, BoardNote{0, SpotType::to_arrive});
        board.addNote(Position{6, 6}, BoardNote{1, SpotType::to_arrive});

        board.sendStateAndChanges();

        Drop dropForBox0 = listener._dropsPerPosition.at(Position{5, 5});
        Drop dropForBox1 = listener._dropsPerPosition.at(Position{6, 6});

        REQUIRE(listener._dropsPerPosition.size() == 2);

        REQUIRE(SpotType::to_arrive == dropForBox0.getSpotType());
        REQUIRE(0 == dropForBox0.getBoxId());

        REQUIRE(SpotType::to_arrive == dropForBox1.getSpotType());
        REQUIRE(1 == dropForBox1.getBoxId());

        // Again, add BoardNotes to Board, request Board send changes. Verify BoardListener received changes.

        board.addNote(Position{5, 5}, BoardNote{0, SpotType::arrive});
        board.addNote(Position{7, 7}, BoardNote{2, SpotType::to_arrive}); 
        board.sendStateAndChanges();
        
        Drop dpForBox0 = listener._dropsPerPosition.at(Position{5, 5});
        Drop dropForBox2 = listener._dropsPerPosition.at(Position{7, 7});
        
        REQUIRE(listener._dropsPerPosition.size() == 2);
        
        REQUIRE(SpotType::arrive == dpForBox0.getSpotType());
        REQUIRE(0 == dpForBox0.getBoxId());

        REQUIRE(SpotType::to_arrive == dropForBox2.getSpotType());
        REQUIRE(2 == dropForBox2.getBoxId());
    }

    SECTION("Verify 1) addNotes() returns false when unsuccessful and 2) BoardListener receives changed Boxes. Using the addNote() method, a box with id of 20 attempts to move to position where a box with id 10 is at. Both boxes' levels go up.")
    {
        int boxId_0 = 0;
        int boxId_1 = 1;
        
        vector<Box> boxes{Box{boxId_0, 0, 1, 1}, Box{boxId_1, 0, 1, 1}};
        Board board{20, 20, std::move(boxes)};
        
        TempListener listener{};
        board.registerListener(&listener);
     
        // Add Box0 at Position{5, 5}. 
        board.addNote(Position{5, 5}, BoardNote{boxId_0, SpotType::to_arrive});

        // Add Box1 to Position{5, 5}.
        // successful should be false and both boxes' levels go up by 1.
        bool successful = board.addNote(Position{5, 5}, BoardNote{boxId_1, SpotType::to_arrive});
        REQUIRE(false == successful);
        
        // Again add Box1 to Position{5, 5}.
        // successful should be false again, and both boxes' levels go up by 1 again.
        successful = board.addNote(Position{5, 5}, BoardNote{boxId_1, SpotType::to_arrive}); 
        REQUIRE(false == successful);
        board.sendStateAndChanges();
       
        REQUIRE(2 == listener._boxes.at(0).getLevel());
        REQUIRE(2 == listener._boxes.at(1).getLevel());
    }


    SECTION("Adding a BoardNote with an unknown BoxId results in an exception.")
    {
        int boxId_0 = 0;
        int boxId_1 = 1;
        
        vector<Box> boxes{Box{boxId_0, 0, 1, 1}, Box{boxId_1, 0, 1, 1}};
        Board board{20, 20, std::move(boxes)};

        // Board does not have a Box id of 100.
        REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{100, SpotType::to_arrive}));
    }
    
    SECTION("Returns a working BoardProxy.")
    {
        // Create boxes with id=0, id=1, and id=2.
        vector<Box> boxes{Box{0, 0, 5, 5}, Box{1, 1, 5, 5}};

        Board board{10, 10, std::move(boxes)};
        BoardProxy boardProxy = board.getBoardProxy();
        TempListener listener{};
        board.registerListener(&listener);

        board.addNote(Position{5, 5}, BoardNote{0, SpotType::to_arrive});
        board.addNote(Position{6, 6}, BoardNote{1, SpotType::to_arrive});

        boardProxy.sendChanges();

        Drop dropForBox0 = listener._dropsPerPosition.at(Position{5, 5});
        Drop dropForBox1 = listener._dropsPerPosition.at(Position{6, 6});

        REQUIRE(listener._dropsPerPosition.size() == 2);

        REQUIRE(SpotType::to_arrive == dropForBox0.getSpotType());
        REQUIRE(0 == dropForBox0.getBoxId());

        REQUIRE(SpotType::to_arrive == dropForBox1.getSpotType());
        REQUIRE(1 == dropForBox1.getBoxId());
    }
}
