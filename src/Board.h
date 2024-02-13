#ifndef FLOBOARD__H
#define FLOBOARD__H

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <utility>
#include <unordered_map>
#include <vector>

#include "BoardCallback.h"
#include "Agent.h"
#include "Box.h"
#include "Position.h"
#include "Spot.h"
class BoardRecorderAgent;
class Board
{
public:
    Board(int width, int height);
    Board(const Board& board) = delete;
    Board(Board&& o) noexcept = delete;
    Board& operator=(const Board& board) = delete;
    Board& operator=(Board&& o) noexcept = delete;
    ~Board() noexcept = default;

    int getWidth() const;
    int getHeight() const;

    bool addNote(Position position, BoardNote boardNote);
    BoardNote getNoteAt(Position position) const;
    void registerCallback(Position pos, BoardCallback& callBack);
    void registerAgent(Agent* agent);
    void sendChanges();

private:
    int _width;
    int _height;
    std::vector<std::vector<Spot>> _spots;
    // TODO these callbacks should be const:w

    std::unordered_map<Position, BoardCallback&> _boardCallbacksPerPos{};    
    std::unordered_set<Agent*> _agents;
    
    mutable std::shared_mutex _mux;
     
};

#endif

