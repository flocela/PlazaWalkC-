#ifndef BOARDRECORDERAGENT__H
#define BOARDRECORDERAGENT__H

#include <vector>
#include <unordered_set>
#include "Agent.h"
#include "Recorder.h"

class Board;
class BoardRecorderAgent : public Agent
{
public:
    // TODO this should be a const Board
    BoardRecorderAgent(Board* board, Recorder* recorder);
    BoardRecorderAgent() = delete;
    BoardRecorderAgent(const BoardRecorderAgent& o) = delete;
    BoardRecorderAgent(BoardRecorderAgent&& o) noexcept = delete;
    BoardRecorderAgent& operator=(const BoardRecorderAgent& o) = delete;
    BoardRecorderAgent& operator=(BoardRecorderAgent&& o) noexcept = delete;
    ~BoardRecorderAgent() noexcept = default;

    void updateWithChanges() override;
    void receiveChanges(std::unordered_map<Position, int> typePerPosition) override;

private:
    Board* _board;
    Recorder* _recorder;
    std::vector<std::unordered_set<Position>> _positionsPerType{};
};

#endif
