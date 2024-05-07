#ifndef BOARDNOTE__H
#define BOARDNOTE__H

#include "SpotType.h"

/*
BoardNote contains a boxId and SpotType.
Note boxId and SpotType do not have any setters and the assignment operators are deleted.
*/
class BoardNote
{

    public:
    
    BoardNote(int boxId, SpotType type);
    BoardNote() = delete;
    BoardNote(const BoardNote& o) = default;
    BoardNote(BoardNote&& o) noexcept = default;
    BoardNote& operator=(const BoardNote& o) = delete;
    BoardNote& operator=(BoardNote&& o) noexcept = delete;
    ~BoardNote() = default;

    SpotType getType() const;
    int getBoxId() const;

    bool operator== (const BoardNote& o) const;


    private:

    SpotType _type;
    int _boxId;

};

namespace std
{
    template<>
    struct hash<BoardNote>
    {
        size_t operator()(const BoardNote& b) const
        {
            // prime numbers
            int A = 21859;
            int B = 86969;
            
            unsigned int h = 97;
            h = (h) ^ (b.getBoxId() * A);
            h = (h) ^ (static_cast<int>(b.getType()) * B);
            return h;
        }
    };
}

#endif
