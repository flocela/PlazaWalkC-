#ifndef BOARD__H
#define BOARD__H

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <utility>
#include <unordered_map>
#include <vector>

#include "BoardCallback.h"
#include "Box.h"
#include "Position.h"
#include "Spot.h"

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
    void registerCallback(BoardCallback* callBack);

private:
    int _width;
    int _height;
    std::vector<std::vector<Spot>> _spots;
    // TODO these callbacks should be const:w

    std::unordered_map<Position, BoardCallback&> _boardCallbacksPerPos{};    
    std::unordered_set<BoardCallback*> _boardCallbacks;
    

    mutable std::shared_mutex _mux;
     
};

#endif

