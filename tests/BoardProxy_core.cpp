#include "catch.hpp"

#include "../src/BoardProxy.h"

using namespace std;

TEST_CASE("BoardProxy_core::")
{
    SECTION("Verify that BoardProxy's sendChanges() method results in a call to Board's sendStateAndChanges() method. The events chain is BoardProxy's sendChanges() method calls Board's sendStateAndChanges() method, which calls BoardListener's receiveChanges() method. Check that BoardListener gets a call to receiveChanges() after BoardProxy's call to sendChanges().")
    {
        class SubListener : public BoardListener 
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
        SubListener listener{};
        board.registerListener(&listener);

        BoardProxy boardProxy = board.getBoardProxy();
        
        boardProxy.sendChanges();
        boardProxy.sendChanges();

        REQUIRE(2 == listener._count);
    }
}
