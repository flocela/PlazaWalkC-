#ifndef BOARDCALLBACK_ACCOUNTANT__H
#define BOARDCALLBACK_ACCOUNTANT__H

#include <unordered_map>
#include <utility>
#include <vector>
#include "Board.h"
#include "BoardCallback.h"

class BoardCallback_Accountant : public BoardCallback
{
public:
    BoardCallback_Accountant(Board* board);
    BoardCallback_Accountant() = delete;
    BoardCallback_Accountant(const BoardCallback_Accountant& o) = delete;
    BoardCallback_Accountant(BoardCallback_Accountant&& o) noexcept = delete;
    BoardCallback_Accountant& operator=(const BoardCallback_Accountant& o) = delete;
    BoardCallback_Accountant& operator=(BoardCallback_Accountant&& o) noexcept = delete;
    ~BoardCallback_Accountant() noexcept = default;

    void callback(Position position) override;

    std::vector< std::pair< std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote > > getNotes() const;
    
private:
    // TODO board should be const.
    Board* _board;
   std::vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote>> _receivedBoardNotes; 

};

#endif
   
