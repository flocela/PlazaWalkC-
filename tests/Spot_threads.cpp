#include "catch.hpp"
#include "../src/Spot.h"
#include <mutex>
#include <regex>
#include <thread>


using namespace std;

mutex _mutex;

/*
Repeatedly (@count number of times) moves a Box with @boxId into @spot. Moving Box means rotating through the SpotTypes from SpotType::left to SpotType::to_leave. The order is SpotType::left, to SpotType::to_arrive, to SpotType::arrive, to SpotType::to_leave, and then back to SpotType::left.

If one of the calls to Spot's changeNote() method throws an exception, then wasException updates to true and function returns.
*/
void funcChangeSpot(Spot* spot, int boxId, int count, bool* wasException)
{
    for (int ii=0; ii<count; ++ii)
    {
        // The return value from changeNote() is true.
        bool changeNoteReturnsTrue = false;

        string exceptionString = "";
        
        try
        {
            changeNoteReturnsTrue =  spot->changeNote(BoardNote{boxId, SpotType::to_arrive}).second;
        }
        catch(const exception & e)
        {
            lock_guard<std::mutex> lock(_mutex);
            *wasException = true;
            exceptionString = e.what();
        }
        
        if (changeNoteReturnsTrue)
        {
            try
            {
                spot->changeNote(BoardNote{boxId, SpotType::arrive});
                spot->changeNote(BoardNote{boxId, SpotType::to_leave});
                spot->changeNote(BoardNote{boxId, SpotType::left});
            }
            catch(const exception & e)
            {
                lock_guard<std::mutex> lock(_mutex);
                *wasException = true;
                exceptionString = e.what();
            }
        }
  
        if (*wasException) 
        { 
            lock_guard<std::mutex> lock(_mutex);
            break;        
        }
    }
}

/*
Repeatedly (@count number of times) calls Spot's getBoardNote() method. If the BoardNote's SpotType is SpotType::left, then verifies that the boxId is -1. If the BoardNote's SpotType is not SpotType::left, then verifies that the boxId is a value other than -1. If either verification fails, then wasInvalid is updated to true, and function returns.
*/
void funcReadSpot(Spot& spot, int count, bool* wasInvalid)
{
    for (int ii=0; ii<count; ++ii)
    {
        BoardNote note = spot.getBoardNote();
        if (note.getType() == SpotType::left &&
            note.getBoxId() != -1)
        {
            lock_guard<mutex> lock(_mutex);
            *wasInvalid = true;
            break;
        }
        if (note.getType() != SpotType::left &&
            note.getBoxId() == -1
           )
        {
            lock_guard<mutex> lock(_mutex);
            *wasInvalid = true;
            break;
        }
    }
}

TEST_CASE("Spot_threads::")
{
    /*
    Remove changeNote()'s unique_lock to make this test fail.
    
    Two threads repeatedly try to change Spot's Note, but because of Spot's unique_lock on changeNote(), one thread always waits for the other thread to finish.")

    If two threads are in the changeNote() method at the same time, they both will read the state of the Spot and both will presume to make their changes to the Spot. Only one thread's change will be saved. Both treads will continue to call the changeNote() method, but only one thread's arugments will be valid. The other thread will set off an exception.

    As an example: Thread1 and Thread2 read that the Spot is SpotType::left. Both presume to change the SpotType to SpotType::to_arrive. Only Thread1's changes are saved. Thread1 continues to make changes from SpotType::to_arrive to SpotType::arrive, to SpotType::to_leave, to SpotType::left. Now the Spot's state is SpotType::left, but Thread2 assuming it is SpotType::to_arrive. Thread2 calls changeNotes() with a SpotType::arrive BoardNote. An exception is thrown. Spot does not accept BoardNotes with SpotTypes of an improper order.
    */
    SECTION("Verify two threads are not in the changeNote() method.")
    {

        bool wasException = false;

        Spot spot{Position{8, 8}};
        std::thread t1(funcChangeSpot, &spot, 100, 1000, &wasException);
        std::thread t2(funcChangeSpot, &spot, 200, 1000, &wasException);

        t1.join();
        t2.join();

        REQUIRE_FALSE(wasException);

    }


    /*
    Remove getBoardNote()'s shared_lock to make this test fail.
    
    One thread repeatedly calls getBoardNote(), the other repeatedly calls changeNote(). Because changeNote() has a unique_lock and getBoardNote() has a shared_lock, getBoardNote() will never return a BoardNote that is half way done.
    
    If one thread is in changeNote() and the other thread is in getBoardNote(), then at some point getBoardNote() will return an invalid BoardNote (say BoxId = 100 and SpotType::left). This means the BoardNote was in the middle of being updated, when it was returned by getBoardNote()."
    */ 
   SECTION("Verify two threads are not in changeNote() and getBoardNote() methods at the same time.")
    {
        bool wasException = false;
        bool wasInvalid = false; 

        Spot spot{Position{8, 8}};
        std::thread t1(funcReadSpot, std::ref(spot), 3000, &wasInvalid);
        std::thread t2(funcChangeSpot, &spot, 100, 3000, &wasException);

        t2.join();
        t1.join();

        REQUIRE_FALSE(wasInvalid);
        REQUIRE_FALSE(wasException);

    }

}
