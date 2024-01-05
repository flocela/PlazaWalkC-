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

    void addNote(Position position, BoardNote boardNote);
    void registerCallback(Position pos, BoardCallback& callBack);

    // returns unordered_map of BoardNotes per boxId.
    std::unordered_map<int, BoardNote> getNotes(Position position) const;

private:
    int _width;
    int _height;
    std::vector<std::vector<Spot>> _spots;
    std::unordered_map<Position, BoardCallback&> _boardCallbacksPerPos{};    
    

    mutable std::shared_mutex _mux;
     
};

#endif

