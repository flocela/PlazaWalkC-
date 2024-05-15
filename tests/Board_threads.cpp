#include "catch.hpp"
#include "../src/Board.h"
#include <thread>
#include <mutex>


using namespace std;

/*
Function used in threading.
For a @times number of times moves Box with boxId @id to Position @pos using a MoveType::to_arrive.
*/
void moveBoxToPosition(Board& board, int id, Position pos, int times)
{
    for (int ii=0; ii<times; ++ii)
    {
         board.changeSpot(pos, BoardNote{id, MoveType::to_arrive}, true);
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


/* Adds @numOfBoxes into different Positions by calling Board's changeSpot() method. Every additional Box moves into an empty Position. It is assumed that @board has all empty Spots at the beginning of the moveBoxesToArrive() function.
*/
void moveBoxesToArrive(Board& board, int numOfBoxes)
{
    for (int ii=0; ii<numOfBoxes; ++ii)
    {
         board.changeSpot(Position{ii, 0}, BoardNote{ii, MoveType::to_arrive}, true);
    }
}

TEST_CASE("Board_threads::")
{

    /*
    Test that there are no changes to the Board's Boxes while their info is being copied in the sendStateAndChanges() method. SendStateAndChanges() is copying the information to send to the Board's BoardListeners. 
    
    To fail test, remove the unique_lock, collectDataLock, found in the sendStateAndChanges() method. collectDataLock uses the same mutex (_mux) that the changeSpot() method uses. In the protected block of code there is a for-loop that copies the BoxInfos into a map, copyOfBoxInfo.

    Box0 is stationed at posA. Box1 repeatedly tries to enter posA. Each time the two Boxes collide their levels increase by one. In another thread, the Boxes' information is copied to be sent, but never while the Boxes are being updated. So, in the received Boxes state the two Boxes' levels will always be equal. It will never be that one Box's level is increased while the other Box's level is yet to be increased. Verifty the sent Boxes' levels are always equal.
   */ 
    SECTION("The Boxes' information is not updated while it is being copied in the sendStateAndChanges() method.")
    {
        // There are only two boxes. They only collide with each other, they both start with a collision level of zero, so their collision levels should always be reported as equal.

        // Thread t1 repeatedly tries to move Box1 into the Position where Box0 is already standing.
        // Thread t2 repeatedly calls to receive the state of the Boxes.

        // When TestListener receives the map of boxesPerId, it checks that both Boxes have the same level. 
        class TestListener : public BoardListener 
        {
        public: 
            bool levelsEqual = true;

            void receiveChanges(unordered_set<Drop> setsOfDropsPerType,
                                unordered_map<int, BoxInfo> boxesPerId) override
            {
                if (boxesPerId.at(0).getLevel() != boxesPerId.at(1).getLevel())
                {
                    levelsEqual = false;
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
      
        board.changeSpot(posA, BoardNote{boxId_0, MoveType::to_arrive}, true);

        std::thread t1(moveBoxToPosition, std::ref(board), boxId_1, posA, 100);
        std::thread t2(requestChanges, std::ref(board), 100);

        t1.join();
        t2.join();

        REQUIRE(listener.levelsEqual);
        
    }
            
    /*
    A complete Drop change has two-parts: a change to the boxId and a change to the MoveType. If the Drop is updated while the _receivingMatrix is being toggled then the first part of the change would be in one matrix, and the second part of the change would be in the other matrix. The _receivingMatrix is only toggled in the sendChanges() method, so adding a lock around this toggling and the changeSpot() method means that the _receivingMatrix will never be toggled during a change.

    If the first part of the change (say the BoxId) could be recorded in one drop matrix and the second part of the change (say the MoveType) were recorded in the second drop matrix, then the sent Drops map would contain partially changed Drops. This would be noticeable because some Drops would have a MoveType::left with a BoxId of NOT -1; this is invalid.

    Thread t1 repeatedly changes Drops from a MoveType::left and BoxId=-1 to a MoveType::to_arrive and a BoxId of NOT -1.

    Thread t2 repeatedly asks for changes to be sent. 

    The sent changes never have a MoveType::left with a BoxId that is not -1. The Drops are always valid. If the unique_lock in sendChanges(), collectDataLock, is removed, then invalid Drops are sent. In order to fail this test: remove the unique_lock, collectDataLock, in sendChanges(). Will also have to add a this_thread::sleep_for(1ms) in changeSpot() (after drop._boxId has been updated, but before drop._type has been updated).

    Adding the sleep in changeSpot() (between the drop.setBoxId() and drop.setMoveType() methods) gives the send-changes thread time to toggle the _receiving matrix between these calls. Leave the sleep in between drop.setBoxId() and drop.setMoveType() and add the unique_lock collectDataLock back in. This will result in a passing test.
    */
    SECTION("Drops sent to BoardListeners have been updated completely. Both their MoveType and boxId have been changed.")
    {
        // Checks that the Drops in receivedChanges are valid. Each Drop must have a MoveType::to_arrive and a BoxId that is NOT -1, or a MoveType::left and a BoxId of -1.
        class BoardListener_Test : public BoardListener 
        {
        public: 
            mutex _mutex;
            bool changeIsComplete = true;

            void receiveChanges(unordered_set<Drop> drops, std::unordered_map<int, BoxInfo> boxes) override
            {
                lock_guard<mutex> gl(_mutex);                
                for (auto& drop : drops)
                {
                    if (drop.getMoveType() == MoveType::left &&
                        drop.getBoxId() != -1)
                    {
                           changeIsComplete = false; 
                    } 
                    if (drop.getMoveType() != MoveType::left &&
                        drop.getBoxId() == -1)
                    {
                           changeIsComplete = false; 
                    }
                }
            }
            
        };

        // Vector of boxes with BoxId's from 0 to 999.
        vector<Box> boxes{};
        for(int ii=0; ii<100; ++ii)
        {
            boxes.push_back(Box{ii, 0, 1, 1});
        }

        Board board{1000, 1000, std::move(boxes)};
        BoardListener_Test listener{};
        board.registerListener(&listener);

        // t1 moves 1000 boxes into 1000 Positions. Each Position is originally MoveType::Left and BoxId=-1. But after the move, the MoveType is MoveType::to_arrive and the BoxId is equal to that particular Box's box id. 
        std::thread t1(moveBoxesToArrive, std::ref(board), 100);
        std::thread t2(requestChanges, std::ref(board), 100);

        t1.join();
        t2.join();

        REQUIRE(listener.changeIsComplete);

    }
}
