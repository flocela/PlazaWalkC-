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
    Board(int height, int width);
    Board(const Board& board) = default;
    Board(Board&& o) noexcept = default;
    Board& operator=(const Board& board);
    Board& operator=(Board&& o) noexcept = default;
    ~Board() noexcept = default;

    void insert(int boxId, int height, int width, int xPos, int yPos);

    int getHeight() const;
    int getWidth() const;
    void setHeight(int height);
    void setWidth(int width);

    std::pair<int, int> getLocation(int boxId) const;

    void move(int boxId, std::vector<Position> positions);

private:
    int _height;
    int _width;
    std::unordered_map<int, std::unique_ptr<Box>> _boxesPerId;


    
};


#endif

