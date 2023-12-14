#ifndef SPOT__H 
#define SPOT__H

#include <unordered_map>
#include "BoardNote.h"
#include "Position.h"

class Spot
{

public:
    Spot(Position pos);
    Spot() = delete;
    Spot(const Spot& o) = default;
    Spot(Spot&& o) noexcept = default;
    Spot& operator=(const Spot& o) = delete;
    Spot& operator=(Spot&& o) = delete;
    ~Spot() = default;

    Position getPosition() const;
    std::unordered_map<int, BoardNote> getNotes() const;

    void tagNote(BoardNote note);


private:
    const Position _position;
    std::unordered_map<int, BoardNote> _notes;

};

#endif
