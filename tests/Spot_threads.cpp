#include "catch.hpp"
#include "../src/Spot.h"
#include <regex>
#include <thread>

using namespace std;

/*
Repeatedly (10,000 times) moves a Box with @boxId into @spot. Each time starting with changing the Spot's SpotType from SpotType::left, to SpotType::to_arrive, to SpotType::arrive, to SpotType::to_leave, and then to SpotType::left. Goes through these SpotTypes 10,000 times.
*/
void funcChangeSpot(Spot& spot, int boxId)
{
    for (int ii=0; ii<10000; ++ii)
    {
        bool successful = false;

        try{
           successful =  spot.changeNote(BoardNote{boxId, SpotType::to_arrive}).second;
        }
        catch(...)
        {
        }
        if (successful)
        {
            try{
                spot.changeNote(BoardNote{boxId, SpotType::arrive});
            }
            catch(...)
            {
            }
            try{
                spot.changeNote(BoardNote{boxId, SpotType::to_leave});
            }
            catch(...)
            {
            }
            try{
                spot.changeNote(BoardNote{boxId, SpotType::left});
            }
            catch(...)
            {
            }
        }
    }
}

/*
Repeatedly (10,000 times) gets the BoardNote at @spot. If the BoardNote's SpotType is SpotType::left, then verifies that the boxId is -1. If the BoardNote's SpotType is not SpotType::left, then verifies that the boxId is not -1.
*/
void funcReadSpot(Spot& spot)
{
    for (int ii=0; ii<10000; ++ii)
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
TEST_CASE("Spot_threads::")
{

    /*
    Remove changeNotes() unique_lock to make this test fail 90% of the time.

    Removing the unique_lock will fail the tests and may result in the following error: RunTests(22617,0x16d58f000) malloc: Region cookie corrupted for region 0x102e00000 (value is 7000001)[0x102e0407c] RunTests(22617,0x16d58f000) malloc: *** set a breakpoint in malloc_error_break to debug
    */
    SECTION("Two threads repeatedly try to change Spot's Note, but because of Spot's unique_lock on changeNote(), one thread always waits for the other thread to finish.")
    {
        // If two threads are in the changeNote() method at the same time, one will be updating the _stateString, while the other is updating the SpotListeners with what it believes to be the completed _stateString.

        // State strings have a B and a number representing the boxId, and a T and a number representing the SpotType. If a _stateString has a T4, that represents a SpotType::left, and for this state string to be valid, it's B portion mus be B-1. If the T portion is not T4 (say T1, T2, or T3) then a valid state string will be B and any positibe number, but not B-1.
        
        // So valid strings are "B200, T2" or "B100, T1". But a string of "B100, T4" or "B-1, T2" is invalid because if the Box has an id, then the Type can not be 4; if the Type is 4, then the boxId must be -1. If the _stateString is invalid, then it is verified that the two threads were inside the changeNote() method at the same time. Since this does not happen, then it is verifid that two threads are not inside changeNote() at the same time.

        std::cmatch match;
        std::regex reg("^(B)(-1|\\d+)(,T)(\\d)$");

        Spot spot{Position{8, 8}};
        SpotListener listener{};
        spot.registerListener(&listener);
        std::thread t1(funcChangeSpot, std::ref(spot), 100);
        std::thread t2(funcChangeSpot, std::ref(spot), 200);

        t1.join();
        t2.join();

        for (string str : listener.getCombinedStrings())
        { 
            std::regex_match(str.c_str(), match, reg);

            // if the boxId is not -1 
            if(match.str(2) == "-1")
            {
                // require that the SpotType be 4
                REQUIRE("4" == match.str(4));
            }

            // if the SpotType is 4
            if(match.str(4) == "4")
            {
                // require tha the boxId not be -1
                REQUIRE("-1" == match.str(2));
            }
        }

    }


    /*
    Remove getBoardNote()'s shared_lock to make this test fail.

    Test may not fail, so in changeNote() add this_thread::sleep_for(10ms) for the case when _type is SpotType::left and a "to arrive" note is not received. This will make it evident that getBoard() is running at the same time as changeNote() because changeNote() will change the _boxId, then wait 10ms before changing the _type. This gives enough time for the thread in getBoardNote() to run and return a noticeably invalid state.
   */ 
    SECTION("One thread repeatedly calls getBoardNote(), the other repeatedly calls changeNote(). Because changeNote() has a unique_lock and getBoardNote() has a shared_lock, getBoardNote() will never return a BoardNote that is half way done.")
    {
        // If one thread is in changeNote() and the other thread is in getBoardNote(), then at some point getBoardNote() will return a BoardNote of {100, SpotType::left} an invalid state. This means the BoardNote was in the middle of being updated, when it was returned by getBoardNote()."

        Spot spot{Position{8, 8}};
        
        std::thread t1(funcReadSpot, std::ref(spot));
        std::thread t2(funcChangeSpot, std::ref(spot), 100);

        t2.join();
        t1.join();

    }
}
