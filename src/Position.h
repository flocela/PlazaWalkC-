#ifndef POSITION__H
#define POSITION__H

#include <iostream>
#include <string>

// Holds an x and y value.
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

    int getX() const;
    int getY() const;
    std::string toString() const;

    bool operator== (const Position& o) const;
    friend std::ostream& operator<< (std::ostream& o, const Position& p)
    {
        o << "[" + std::to_string(p.getX()) + ", " + std::to_string(p.getY()) << "]";
        return o;
    }
    
    private:

    int _x = 0;
    int _y = 0;
};

namespace std
{
    template<>
    struct hash<Position>
    {
        size_t operator()(const Position& p) const
        {
            return ( hash<int>()(p.getX()) ^ (hash<int>()(p.getY()) << 1) );
        }
    };
}

#endif
