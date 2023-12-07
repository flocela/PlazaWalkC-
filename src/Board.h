#ifndef BOARD__H
#define BOARD__H

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Box.h"
#include "Position.h"

class Board
{
public:
    Board(int width, int height);
    Board(const Board& board) = default;
    Board(Board&& o) noexcept = default;
    Board& operator=(const Board& board);
    Board& operator=(Board&& o) noexcept = default;
    ~Board() noexcept = default;

    void insert(int boxId, int height, int width, int xPos, int yPos);

    int getWidth() const;
    int getHeight() const;
    void setWidth(int width);
    void setHeight(int height);

    Position getLocation(int boxId) const;

    void move(int boxId, std::vector<Position> positions);
    
    std::vector<Box> getCopyOfBoxes () const;

private:
    int _width;
    int _height;
    std::unordered_map<int, std::unique_ptr<Box>> _boxesPerId;
    std::vector<std::vector<int>> _boxIdsOnBoard;

    
};

#endif

