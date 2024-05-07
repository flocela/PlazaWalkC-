#include "catch.hpp"

#include "../src/BroadcastAgent.h"

using namespace std;

TEST_CASE("BroadcastAgent_core::")
{
    SECTION("Calling requestBroadcast() causes BoardProxy to call its sendChanges() method. The chain of evens is: BroadcastAgent's requestBroadcast() method is called. Inside requestBroadcast(), BoardProxy's sendChanges() method is called. Inside the sendChanges() method, Board's sendStateAndChanges() method is called. Inside sendStateAndChages() BoardListener's receiveChanges is called. Verify BoardListener receives changes when BoardProxy's requestBroadcast() method is called.")
    {

        class TestListener : public BoardListener 
        {
        public: 

            void receiveChanges(unordered_set<Drop> setOfDropsPerType,
                                unordered_map<int, BoxInfo> boxesPerId) override
            {
                try
                {
                    ++_count;
                }
                catch(...)
                {
                    return;
                }
            }
       
            // counts how many times receivedChanges is called. 
            int _count = 0;
            
        };

        Board board{20, 20, vector<Box>{}};
        TestListener listener{};
        board.registerListener(&listener);

        BoardProxy boardProxy = board.getBoardProxy();
        BroadcastAgent agent{std::move(boardProxy)};

        agent.requestBroadcast();
        agent.requestBroadcast();

        REQUIRE(2 == listener._count);
    }
}
