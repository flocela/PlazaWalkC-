#include "catch.hpp"
#include "../src/Board.h"
#include <thread>

using namespace std;

void moveBoxToPosition(Board& board, int id, Position pos, int times)
{
    for (int ii=0; ii<times; ++ii)
    {
         board.addNote(pos, BoardNote{id, SpotType::to_arrive});
    }
}

void requestChanges(Board& board, int times)
{
    for (int ii=0; ii<times; ++ii)
    {
        board.sendChanges();
    }
}
// Moves numOfBoxes into new Positions by adding BoardNotes with MovementType::to_arrive. Assumes Board initially has only empty Positions, all of MovementType::left.
void moveBoxesToArrive(Board& board, int numOfBoxes)
{
    for (int ii=0; ii<numOfBoxes; ++ii)
    {
         board.addNote(Position{ii, 0}, BoardNote{ii, SpotType::to_arrive});
    }
}

TEST_CASE("Board_threads::")
{
    // The method sendChanges() contains a block of code protected with the unique_lock lockUq. In that block there is a for-loop that copies the BoxInfos into the copyOfBoxInfo map. To make this test fail, move that for-loop outside of the lockUq block.
    SECTION("Two boxes collide (one box tries to enter the position of another box). Each box's level will increase by one. The state of the boxes will never be sent having one box's level increased while the other box's level is  yet to be increased. Before changes are sent in sendChanges() both boxes' levels will have been increased.")
    {
        // There are only two boxes. They only collide with each other, they both start with a collision level of zero, so their collision levels should always be reported as equal.
        // Thread t1 repeatedly tries to move Box with id = 1 into the position where Box with id = 0 is already standing.
        // Thread t2 repeatedly calls to receive the state of the Boxes.

        // When TestListener receives the map of boxesPerId, it checks that both boxes have the same level. 
        class TestListener : public BoardListener 
        {
        public: 

            void receiveChanges(unordered_map<SpotType, unordered_set<Drop>> setsOfDropsPerType,
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
        
        vector<Box> boxes{Box{boxId_0, 0, 1, 1}, Box{boxId_1, 0, 1, 1}};
        Board board{20, 20, std::move(boxes)};
        TestListener listener{};
        board.registerListener(&listener);
      
        board.addNote(Position{5, 5}, BoardNote{boxId_0, SpotType::to_arrive});

        std::thread t1(moveBoxToPosition, std::ref(board), boxId_1, Position{5, 5}, 100);
        std::thread t2(requestChanges, std::ref(board), 100);

        t1.join();
        t2.join();
        
    }

            
    // In order to fail this test: remove the unique_lock, lockUq, in sendChanges(). May also have to add a this_thread::sleep_for(1ms) in addNote (after drop._boxId has been updated, but before drop._type has been updated).

    // A complete Drop change has two-parts: a change to the boxId and a change to the Movement::Type. If the change in the Drop were to happen while the _receivingMatrix was being toggled then the first part of the change would be in one matrix, and the second part of the change would be in the other matrix. The _receivingMatrix is only toggled in the sendChanges() method, so adding a lock around this toggling and the addNote() method means that the _receivingMatrix will never be toggled during a change.

    // If the first part of the change (say the BoxId) could be recorded in one drop matrix and the second part of the change (say the MovementType) were recorded in the second drop matrix, then the sent changes would have partially changed Drops. This would be noticeable because some Drops would have a MovementType::left with a BoxId of not -1. This is invalid.

    // Thread t1 repeatedly changes Drops from a MovementType::left and BoxId=-1 to a MovementType::to_arrive and a BoxId of not -1.

    // Thread t2 repeatedly asks for changes to be sent. 

    // The resulting changes never have a MovementType::left with a BoxId that is not -1. The Drops are always valid. If the unique_lock in sendChanges() is removed, then these invalid Drops are sent.

    SECTION("Drops sent to BoardListeners are changed properly. Both their MovementType and BoxId have been changed.")
    {
        // Checks that the Drops in receivedChanges are valid. The Drop has a MovementType::to_arrive and a BoxId that is not -1. Or the Drop has a MovementType::left and a BoxId of -1.
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
                        try
                        {
                            if (type == SpotType::left)
                            {
                                    REQUIRE(drop.getBoxId()== -1);
                            } 
                            if (type != SpotType::left)
                            {
                                    REQUIRE(drop.getBoxId()!= -1);
                            }
                        }
                        catch(...)
                        {
                            return;
                        }
                    }
                }
            }
            
        };

        // Vector of boxes with BoxId's from 0 to 1999.
        vector<Box> boxes{};
        for(int ii=0; ii<1000; ++ii)
        {
            boxes.push_back(Box{ii, 0, 1, 1});
        }

        Board board{1000, 1000, std::move(boxes)};
        BoardListener_Test listener{};
        board.registerListener(&listener);

        // t1 moves 1000 boxes into 1000 Positions. Each Position is originally MoveType::Left and BoxId=-1. But after the move, the MoveType is MoveType::to_arrive and the BoxId is equal to that particular Box's box id. 
        std::thread t1(moveBoxesToArrive, std::ref(board), 1000);
        std::thread t2(requestChanges, std::ref(board), 1000);

        t1.join();
        t2.join();

    }
}
