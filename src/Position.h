#ifndef POSITION__H
#define POSITION__H

class Position
{
public:
    Position(int x, int y);
    Position() = delete;
    Position(const Position& o) = default;
    Position(Position&& o) noexcept = default;
    Position& operator=(const Position& o) = default;
    Position& operator=(Position&& o) noexcept = default;
    ~Position() noexcept = default;

    int getX();
    int getY();

private:
    int _x = 0;
    int _y = 0;
};

#endif
