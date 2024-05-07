#include "catch.hpp"
#include "../src/Board.h"
#include "../src/NoteAccountant.h"

using namespace std;

/* 
TempListener is a BoardListener that saves the last Drops and Boxes that were received in the last call to receiveChanges().
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

TEST_CASE("Board_core::")
{
    // BoxId's 0, 1, and 2.    
    int boxId_0 = 0;
    int boxId_1 = 1;
    int boxId_2 = 2;

    // Create Boxes with id=0, id=1, and id=2.
    vector<Box> boxes{
        Box{boxId_0, 0, 5, 5},
        Box{boxId_1, 1, 5, 5},
        Box{boxId_2, 2, 5, 5}};

    // Create Board.
    Board board{20, 20, std::move(boxes)};

    // Add Listener.
    TempListener listener{};
    board.registerListener(&listener);
    
    // Positions.    
    Position posA{Position{5, 5}};
    Position posB{Position{6, 6}};
    Position posC{Position{7, 7}};
    
    SECTION("Insert BoardNotes with different types at posA. Verifty the getNoteAt() method returns the new BoardNote after each insertion.")
    {  
        board.addNote(posA, BoardNote{boxId_0, SpotType::to_arrive});
        REQUIRE(board.getNoteAt(posA) == BoardNote{boxId_0, SpotType::to_arrive});

        board.addNote(posA, BoardNote{boxId_0, SpotType::arrive});
        REQUIRE(board.getNoteAt(posA) == BoardNote{boxId_0, SpotType::arrive});

        board.addNote(posA, BoardNote{boxId_0, SpotType::to_leave});
        REQUIRE(board.getNoteAt(posA) == BoardNote{boxId_0, SpotType::to_leave});

        board.addNote(posA, BoardNote{boxId_0, SpotType::left});
        REQUIRE(board.getNoteAt(posA) == BoardNote{-1, SpotType::left});

    }


    SECTION("Verify changes to Board's Spots are sent to the BoardListener when board.sendStateAndChanges() is called.")
    {

        board.addNote(posA, BoardNote{boxId_0, SpotType::to_arrive});
        board.addNote(posB, BoardNote{boxId_1, SpotType::to_arrive});

        board.sendStateAndChanges();
        
        REQUIRE(listener._dropsPerPosition.size() == 2);

        Drop drop0 = listener._dropsPerPosition.at(posA);
        Drop drop1 = listener._dropsPerPosition.at(posB);

        REQUIRE(SpotType::to_arrive == drop0.getSpotType());
        REQUIRE(boxId_0 == drop0.getBoxId());

        REQUIRE(SpotType::to_arrive == drop1.getSpotType());
        REQUIRE(boxId_1 == drop1.getBoxId());

        // Again,
        // add BoardNotes to Board, request Board send changes. Verify BoardListener received changes.
        board.addNote(posA, BoardNote{boxId_0, SpotType::arrive});
        board.addNote(posC, BoardNote{boxId_2, SpotType::to_arrive}); 

        board.sendStateAndChanges();
        
        REQUIRE(listener._dropsPerPosition.size() == 2);
        
        Drop dp0 = listener._dropsPerPosition.at(posA);
        Drop drop2 = listener._dropsPerPosition.at(posC);
        
        REQUIRE(SpotType::arrive == dp0.getSpotType());
        REQUIRE(boxId_0 == dp0.getBoxId());

        REQUIRE(SpotType::to_arrive == drop2.getSpotType());
        REQUIRE(boxId_2 == drop2.getBoxId());
    }

    SECTION("When addNotes() is unsuccessful verify 1) addNotes() returns false and 2) both Boxes' levels go up. ")
    {
        // Add Box0 to posA.
        board.addNote(posA, BoardNote{boxId_0, SpotType::to_arrive});

        // Try to add Box1 to posA.
        bool isSuccessful = board.addNote(posA, BoardNote{boxId_1, SpotType::to_arrive});

        // Verify isSuccessful. Note both boxes' levels go up by 1.
        REQUIRE(false == isSuccessful);
        
        // Again, try to add Box1 to posA.
        isSuccessful = board.addNote(posA, BoardNote{boxId_1, SpotType::to_arrive}); 

        // Verify isSuccessful is false again. Both Boxes' levels go up by one again.
        REQUIRE(false == isSuccessful);

        // Call Board's sendStateAndChanges method().
        board.sendStateAndChanges();

        // Verify Boxes' levels are 2.
        REQUIRE(2 == listener._boxes.at(0).getLevel());
        REQUIRE(2 == listener._boxes.at(1).getLevel());
    }


    SECTION("Verifty adding a BoardNote with an unknown BoxId results in an exception.")
    {
        // Board does not have a Box id of 100.
        REQUIRE_THROWS(board.addNote(posA, BoardNote{100, SpotType::to_arrive}));
    }
    
    SECTION("Verifty getBoardProxy() returns a working BoardProxy.")
    {
        BoardProxy boardProxy = board.getBoardProxy();

        board.addNote(posA, BoardNote{boxId_0, SpotType::to_arrive});
        board.addNote(posB, BoardNote{boxId_1, SpotType::to_arrive});

        // BoardProxy calls Board's sendStateAndChanges() method.
        boardProxy.sendChanges();

        Drop drop0 = listener._dropsPerPosition.at(posA);
        Drop drop1 = listener._dropsPerPosition.at(posB);

        REQUIRE(listener._dropsPerPosition.size() == 2);

        REQUIRE(SpotType::to_arrive == drop0.getSpotType());
        REQUIRE(boxId_0 == drop0.getBoxId());

        REQUIRE(SpotType::to_arrive == drop1.getSpotType());
        REQUIRE(boxId_1 == drop1.getBoxId());
    }

    SECTION("Verify NoteSubscribers receive changes to the Spot they are associatd with.")
    {
        NoteAccountant noteSubscriber{};
        board.registerNoteSubscriber(posA, noteSubscriber);
       
        // box 0 is about to arrive. 
        board.addNote(posA, BoardNote{boxId_0, SpotType::to_arrive});

        // box 0 arrives.
        board.addNote(posA, BoardNote{boxId_0, SpotType::arrive});

        vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote>> callbackNotes = noteSubscriber.getNotes();

        REQUIRE(2 == callbackNotes.size());
        REQUIRE(BoardNote{0, SpotType::to_arrive} == callbackNotes[0].second);
        REQUIRE(BoardNote{0, SpotType::arrive}  == callbackNotes[1].second);
    }

}
