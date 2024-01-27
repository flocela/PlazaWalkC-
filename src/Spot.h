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
    int getBoxId() const;
    int getType() const;

    bool tagNote(BoardNote note);


private:
    const Position _position;
    int _boxId = -1;
    int _type = -1;

};

#endif
