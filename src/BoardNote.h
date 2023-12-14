#ifndef BOARDNOTE__H
#define BOARDNOTE__H

#include "Position.h"

class BoardNote
{

public:
    BoardNote(int type, int boxId);
    BoardNote() = delete;
    BoardNote(const BoardNote& o) = default;
    BoardNote(BoardNote&& o) noexcept = default;
    BoardNote& operator=(const BoardNote& o) = delete;
    BoardNote& operator=(BoardNote&& o) noexcept = delete;
    ~BoardNote() = default;

    int getType() const;
    int getBoxId() const;

    bool operator== (const BoardNote& o) const;

private:
    const int _type;
    const int _boxId;

};

namespace std
{
    template<>
    struct hash<BoardNote>
    {
        size_t operator()(const BoardNote& b) const
        {   return  (hash<int>()(b.getType()) ^ (hash<int>()(b.getBoxId()) << 1));
        }
    };
}

#endif
