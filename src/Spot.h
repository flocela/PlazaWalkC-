#ifndef SPOT__H 
#define SPOT__H

#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <vector>
#include "BoardNote.h"
#include "Position.h"
#include "SpotListener.h"

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

    bool changeNote(BoardNote note);

    void registerListener(SpotListener* listener);
    


private:
    Position _position;
    int _boxId = -1;
    int _type = -1;
    std::string _combined = "-1,-1";
    
    std::string errorString(BoardNote boardNote);

    mutable std::shared_mutex _mm;

    std::vector<SpotListener*> _listeners{};

    void updateCombinedString();

    void notifyListeners();

};

#endif
