#ifndef SPOT__H 
#define SPOT__H

#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include "BoardNote.h"
#include "Position.h"

class Spot
{

public:
    Spot(Position pos);
    Spot() = delete;
    Spot(const Spot& o);
    Spot(Spot&& o) noexcept;
    Spot& operator=(const Spot& o) = delete;
    Spot& operator=(Spot&& o) = delete;
    ~Spot() = default;

    Position getPosition() const;
    BoardNote getBoardNote() const;

    bool tagNote(BoardNote note);


private:
    Position _position;
    int _boxId = -1;
    int _type = -1;
    
    std::string errorString(BoardNote boardNote);

    mutable std::shared_mutex _mm;

};

#endif
