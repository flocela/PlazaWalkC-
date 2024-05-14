#include "catch.hpp"
#include "../src/Spot.h"
#include <regex>
#include <thread>

using namespace std;

/*
Repeatedly (10,000 times) moves a Box with @boxId into @spot. Each time starting with changing the Spot's SpotType from SpotType::left, to SpotType::to_arrive, to SpotType::arrive, to SpotType::to_leave, and then to SpotType::left. Goes through these SpotTypes 10,000 times.
*/
void funcChangeSpot(Spot* spot, int boxId)
{
    for (int ii=0; ii<10000; ++ii)
    {
        bool successful = false;

        REQUIRE_NOTHROW(successful =  spot->changeNote(BoardNote{boxId, SpotType::to_arrive}).second);
        
        if (successful)
        {
            REQUIRE_NOTHROW(spot->changeNote(BoardNote{boxId, SpotType::arrive}));
            REQUIRE_NOTHROW(spot->changeNote(BoardNote{boxId, SpotType::to_leave}));
            REQUIRE_NOTHROW(spot->changeNote(BoardNote{boxId, SpotType::left}));
        }
    }
}

/*
Repeatedly (10,000 times) gets the BoardNote at @spot. If the BoardNote's SpotType is SpotType::left, then verifies that the boxId is -1. If the BoardNote's SpotType is not SpotType::left, then verifies that the boxId is not -1.
*/
void funcReadSpot(Spot& spot)
{
    for (int ii=0; ii<1000; ++ii)
    {
        BoardNote note = spot.getBoardNote();
        if (note.getType() == SpotType::left)
        {
            REQUIRE( note.getBoxId() == -1 );
        }
        if (note.getBoxId() == -1)
        {
            REQUIRE( note.getType() == SpotType::left );
        }
    }
}

/*
When making these two SECTIONS fail, run them separately. When they fail they cause exceptions, which will stop the other thread mid run.
*/
TEST_CASE("Spot_threads::")
{

    /*
    Remove changeNote()'s unique_lock to make this test fail.
    */
    SECTION("Two threads repeatedly try to change Spot's Note, but because of Spot's unique_lock on changeNote(), one thread always waits for the other thread to finish.")
    {
        // If two threads are in the changeNote() method at the same time, they both will read the state of the Spot and both will make their changes to the Spot. Only one thread's change will be saved. One thread will continue with its next change to the Spot. The other will set off an exception. It will try to make a change to a Spot but the Spot's underlying state will not be correct.

        // As an example. Thread1 and Thread2 read that the Spot is SpotType::left. Both persume to change the SpotType to SpotType::to_arrive. Only Thread1's changes are saved. Thread1 continues to make changes from SpotType::to_arrive to SpotType::arrive, to SpotType::to_leave, to SpotType::left. Now the Spot's state is SpotType::left and Thread2 presuming its SpotType is to_arrive sends a SpotType::arrive BoardNote. An exception is thrown. Spot does not accept BoardNotes that are not in the proper order.

        Spot spot{Position{8, 8}};
        std::thread t1(funcChangeSpot, &spot, 100);
        std::thread t2(funcChangeSpot, &spot, 200);

        t1.join();
        t2.join();

    }


    /*
    Remove getBoardNote()'s shared_lock to make this test fail.

    Test may not fail by removing shared_lock, so add a thread sleep.

    Thread t1 calls funcReadSpot().
    Thread t2 calls funcChangeSpot().
    
    In changeNote() add this_thread::sleep_for(10ms) for the case when _type is SpotType::left and a "to arrive" BoardNote is received. This will make it evident that a thread is in getBoard() while another thread is in changeNote(). changeNote() will change the _boxId, then wait 10ms before changing the _type. During this wait time the Spot's state is invalid. getBoardNote() will read the state and return an invalid state.
    */ 
   SECTION("One thread repeatedly calls getBoardNote(), the other repeatedly calls changeNote(). Because changeNote() has a unique_lock and getBoardNote() has a shared_lock, getBoardNote() will never return a BoardNote that is half way done.")
    {
        // If one thread is in changeNote() and the other thread is in getBoardNote(), then at some point getBoardNote() will return an invalid BoardNote (say BoxId = 100 and SpotType::left). This means the BoardNote was in the middle of being updated, when it was returned by getBoardNote()."

        Spot spot{Position{8, 8}};
        
        std::thread t1(funcReadSpot, std::ref(spot));
        std::thread t2(funcChangeSpot, &spot, 100);

        t2.join();
        t1.join();

    }

}
