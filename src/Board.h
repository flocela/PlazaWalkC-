#ifndef BOARD__H
#define BOARD__H

#include <vector>

#include "Box.h"

class Board
{
public:
    Board(int height, int width, std::vector<Box*> boxes);
    Board(const Board& board) = default;
    Board(Board&& o) noexcept = default;
    Board& operator=(const Board& board);
    Board& operator=(Board&& o) noexcept = default;
    ~Board() noexcept = default;

    int getHeight() const;
    int getWidth() const;
    void setHeight(int height);
    void setWidth(int width);

private:
    int _height;
    int _width;
    std::vector<Box*> _boxes;


    
};


#endif

