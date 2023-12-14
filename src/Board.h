#ifndef BOARD__H
#define BOARD__H

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Box.h"
#include "Position.h"
#include <mutex>

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

    // _boxesPerId helps find the location of a box on the board quickly
    // by getting the location from the box, which is easy to find using this 
    // map and seeing if it matches the box's location in _boxIdsOnBoard.
    std::unordered_map<int, std::unique_ptr<Box>> _boxesPerId;
    
    // _boxIdsOnBoard is the official location of the boxes on the board.
    std::vector<std::vector<int>> _boxIdsOnBoard;

    void move(int boxId, Position pos);
    
};

#endif

