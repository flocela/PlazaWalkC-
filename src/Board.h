#ifndef BOARD__H
#define BOARD__H

#include <memory>
#include <utility>
#include <vector>

#include "Box.h"
#include "Position.h"
#include "Spot.h"

class Board
{
public:
    Board(int width, int height);
    Board(const Board& board) = default;
    Board(Board&& o) noexcept = default;
    Board& operator=(const Board& board);
    Board& operator=(Board&& o) noexcept = default;
    ~Board() noexcept = default;

    int getWidth() const;
    int getHeight() const;

    void addNote(Position position, BoardNote boardNote);

    // returns unordered_map of BoardNotes per boxId.
    std::unordered_map<int, BoardNote> getNotes(Position position) const;

private:
    int _width;
    int _height;
    std::vector<std::vector<Spot>> _spots;   
     
};

#endif

