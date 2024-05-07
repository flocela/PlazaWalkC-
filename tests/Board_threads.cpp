#include "catch.hpp"
#include "../src/Board.h"
#include <thread>

using namespace std;

/*
Function used in threading.
For a @times number of times moves Box with boxId @id to Position @pos using a SpotType of SpotType::to_arrive.
*/
void moveBoxToPosition(Board& board, int id, Position pos, int times)
{
    for (int ii=0; ii<times; ++ii)
    {
         board.addNote(pos, BoardNote{id, SpotType::to_arrive});
    }
}


/*
Function used in threading.
For a @times number of times calls @board's sendStateAndChanges() method.
*/
void requestChanges(Board& board, int times)
{
    for (int ii=0; ii<times; ++ii)
    {
        board.sendStateAndChanges();
    }
}


/* Adds @numOfBoxes into different Positions by calling Board's addNote() method. Every additional Box moves into an empty Position. It is assumed that @board has all empty Spots at the beginning of the moveBoxesToArrive() mthod.
*/
void moveBoxesToArrive(Board& board, int numOfBoxes)
{
    for (int ii=0; ii<numOfBoxes; ++ii)
    {
         board.addNote(Position{ii, 0}, BoardNote{ii, SpotType::to_arrive});
    }
}

TEST_CASE("Board_threads::")
{

    /*
    Test that there are no changes to the Board's Boxes while the sendStateAndChanges() method copies the Boxes' information into a map to send to the BoardListeners. 
    
    The method sendStateAndChanges() contains a block of code protected with the unique_lock collectDataLock that uses the same mutex (_mux) that the addNote() method uses. In that block there is a for-loop that copies the BoxInfos into the copyOfBoxInfo map. To make this test fail, move that copying-for-loop outside of the collectDataLock block.
    */
    SECTION("Box0 is stationed at posA. Box1 repeatedly tries to enter posA. Each time the two Boxes collide their levels increase by one. The Boxes' information is copied to be sent, but never while the Boxes are being updated. So, the sent state of the Boxes will never be that one Box's level is increased while the other Box's level is yet to be increased. Verifty the sent Boxes' levels are always equal.")
    {
        // There are only two boxes. They only collide with each other, they both start with a collision level of zero, so their collision levels should always be reported as equal.

        // Thread t1 repeatedly tries to move Box1 into the Position where Box0 is already standing.
        // Thread t2 repeatedly calls to receive the state of the Boxes.

        // When TestListener receives the map of boxesPerId, it checks that both Boxes have the same level. 
        class TestListener : public BoardListener 
        {
        public: 

            void receiveChanges(unordered_set<Drop> setsOfDropsPerType,
                                unordered_map<int, BoxInfo> boxesPerId) override
            {
                try
                {
                    REQUIRE(boxesPerId.at(0).getLevel() == boxesPerId.at(1).getLevel());
                }
                catch(...)
                {
                    return;
                }
            }
            
        };

        int boxId_0 = 0;
        int boxId_1 = 1;
        Position posA = Position{5, 5};
        
        vector<Box> boxes{Box{boxId_0, 0, 1, 1}, Box{boxId_1, 0, 1, 1}};
        Board board{20, 20, std::move(boxes)};
        TestListener listener{};
        board.registerListener(&listener);
      
        board.addNote(posA, BoardNote{boxId_0, SpotType::to_arrive});

        std::thread t1(moveBoxToPosition, std::ref(board), boxId_1, posA, 100);
        std::thread t2(requestChanges, std::ref(board), 100);

        t1.join();
        t2.join();
        
    }

            
    /*
    A complete Drop change has two-parts: a change to the boxId and a change to the SpotType. If the change in the Drop were to happen while the _receivingMatrix was being toggled then the first part of the change would be in one matrix, and the second part of the change would be in the other matrix. The _receivingMatrix is only toggled in the sendChanges() method, so adding a lock around this toggling and the addNote() method means that the _receivingMatrix will never be toggled during a change.

    If the first part of the change (say the BoxId) could be recorded in one drop matrix and the second part of the change (say the SpotType) were recorded in the second drop matrix, then the sent changes would have partially changed Drops. This would be noticeable because some Drops would have a SpotType::left with a BoxId of NOT -1; this is invalid.

    Thread t1 repeatedly changes Drops from a SpotType::left and BoxId=-1 to a SpotType::to_arrive and a BoxId of NOT -1.

    Thread t2 repeatedly asks for changes to be sent. 

    The resulting changes never have a SpotType::left with a BoxId that is not -1. The Drops are always valid. If the unique_lock in sendChanges() is removed, then invalid Drops are sent. In order to fail this test: remove the unique_lock, collectDataLock, in sendChanges(). May also have to add a this_thread::sleep_for(1ms) in addNote (after drop._boxId has been updated, but before drop._type has been updated).
    */
    SECTION("Drops sent to BoardListeners are changed properly. Both their SpotType and boxId have been changed.")
    {
        // Checks that the Drops in receivedChanges are valid. The Drop has a SpotType::to_arrive and a BoxId that is NOT -1. Or the Drop has a SpotType::left and a BoxId of -1.
        class BoardListener_Test : public BoardListener 
        {
        public: 

            void receiveChanges(unordered_set<Drop> drops, std::unordered_map<int, BoxInfo> boxes) override
            {
                for (auto& drop : drops)
                {
                    try
                    {
                        if (drop.getSpotType() == SpotType::left)
                        {
                                REQUIRE(drop.getBoxId() == -1);
                        } 
                        if (drop.getSpotType() != SpotType::left)
                        {
                                REQUIRE(drop.getBoxId() != -1);
                        }
                    }
                    catch(...)
                    {
                        return;
                    }
                }
            }
            
        };

        // Vector of boxes with BoxId's from 0 to 999.
        vector<Box> boxes{};
        for(int ii=0; ii<1000; ++ii)
        {
            boxes.push_back(Box{ii, 0, 1, 1});
        }

        Board board{1000, 1000, std::move(boxes)};
        BoardListener_Test listener{};
        board.registerListener(&listener);

        // t1 moves 1000 boxes into 1000 Positions. Each Position is originally SpotType::Left and BoxId=-1. But after the move, the SpotType is SpotType::to_arrive and the BoxId is equal to that particular Box's box id. 
        std::thread t1(moveBoxesToArrive, std::ref(board), 1000);
        std::thread t2(requestChanges, std::ref(board), 1000);

        t1.join();
        t2.join();

    }
}
