#ifndef BOARDAGENT__H
#define BOARDAGENT__H

#include <vector>
#include <unordered_set>
#include "Agent.h"
//#include "Board.h"
#include "BoardAgentListener.h"

class Board;

class BoardAgent : public Agent
{
public:
    // TODO this should be a const Board
    BoardAgent(Board* board);
    BoardAgent() = delete;
    BoardAgent(const BoardAgent& o) = delete;
    BoardAgent(BoardAgent&& o) noexcept = delete;
    BoardAgent& operator=(const BoardAgent& o) = delete;
    BoardAgent& operator=(BoardAgent&& o) noexcept = delete;
    ~BoardAgent() noexcept = default;

    void updateWithChanges() override;
    void receiveChanges(std::unordered_map<Position, int> typePerPosition) override;

    void registerListener(BoardAgentListener* listener);

private:
    Board* _board;
    std::vector<BoardAgentListener*> _listeners;
    std::vector<std::unordered_set<Position>> _positionsPerType{};
};

#endif
