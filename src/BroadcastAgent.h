#ifndef BROADCASTAGENT__H
#define BROADCASTAGENT__H

#include <vector>
#include <unordered_set>
#include "Agent.h"
#include "Board.h"

class BroadcastAgent : public Agent
{
public:
    // TODO this should be a const Board
    BroadcastAgent(Board* board);
    BroadcastAgent() = delete;
    BroadcastAgent(const BroadcastAgent& o) = delete;
    BroadcastAgent(BroadcastAgent&& o) noexcept = delete;
    BroadcastAgent& operator=(const BroadcastAgent& o) = delete;
    BroadcastAgent& operator=(BroadcastAgent&& o) noexcept = delete;
    ~BroadcastAgent() noexcept = default;

    void updateWithChanges() override;

private:
    Board* _board;
};

#endif
