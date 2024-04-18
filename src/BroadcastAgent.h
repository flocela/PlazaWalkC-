#ifndef BROADCASTAGENT__H
#define BROADCASTAGENT__H

#include "Agent.h"
#include "BoardProxy.h"

class BroadcastAgent : public Agent
{
public:
    BroadcastAgent(BoardProxy&& boardProxy);
    BroadcastAgent() = delete;
    BroadcastAgent(const BroadcastAgent& o) = delete;
    BroadcastAgent(BroadcastAgent&& o) noexcept = delete;
    BroadcastAgent& operator=(const BroadcastAgent& o) = delete;
    BroadcastAgent& operator=(BroadcastAgent&& o) noexcept = delete;
    ~BroadcastAgent() noexcept = default;

    // Calls BoardProxy's sendChanges() method, so that board can broadcast its changes.
    void requestBroadcastChanges() override;

private:
    BoardProxy _boardProxy;
};

#endif
