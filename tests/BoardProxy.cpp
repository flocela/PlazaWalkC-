#include "catch.hpp"

#include "../src/BoardProxy.h"

using namespace std;

TEST_CASE("calling sendChanges() causes Board to call its sendChanges()")
{
    class TestListener : public BoardListener 
    {
    public: 

        void receiveChanges(unordered_map<SpotType, unordered_set<Drop>> setOfDropsPerType,
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

    BoardProxy boardProxy{board};
    
    boardProxy.sendChanges();
    boardProxy.sendChanges();

    REQUIRE(2 == listener._count);
}


