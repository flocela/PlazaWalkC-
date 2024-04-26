#include "catch.hpp"
#include <iostream>
#include "../src/Spot.h"
#include <regex>
#include <thread>

using namespace std;

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

    // Remove changeNotes() unique_lock to make this test fail 90% of the time.
    // Removing the unique_lock will fail the tests and may result in the following error: RunTests(22617,0x16d58f000) malloc: Region cookie corrupted for region 0x102e00000 (value is 7000001)[0x102e0407c] RunTests(22617,0x16d58f000) malloc: *** set a breakpoint in malloc_error_break to debug
    
    SECTION("two threads repeatedly try to change Spot's Note, but because of Spot's unique_lock on changeNote(), one thread always waits for the other thread to finish.")
    {
        // If two threads are in the changeNote() method at the same time, one will be updating the _stateString, while the other is returning what it believes to be the completed _stateString.

        // When a Spot is empty, the the type is '4', corresponding to SpotType::left, and the boxId must be -1. So valid strings are B200,T2 or B100,T1. But a string of B100,T4 or B-1,T2 is invalid because if the Box has an id, then the Type can not be 4; if the Type is 4, then the boxId must be -1. If the _stateString is invalid, then two threads were inside the changeNote() method at the same time.

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
            if(match.str(2) == "-1")
            {
                REQUIRE("4" == match.str(4));
            }
            if(match.str(4) == "4")
            {
                REQUIRE("-1" == match.str(2));
            }
        }

    }


    // Remove getBoardNote()'s shared_lock to make this test fail.
    // Test may not fail, so in changeNote() add this_thread::sleep_for(10ms) for the case when _type is SpotType::left and a "to arrive" note is not received. This will make it evident that getBoard() is running at the same time as changeNote() because changeNote() will change the _boxId, then wait 10ms before changing the _type. This gives enough time for the thread in getBoardNote() to run and return a noticeably invalid state.
    
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
