#ifndef SPOT__H 
#define SPOT__H

#include <shared_mutex>
#include <vector>
#include "BoardNote.h"
#include "Position.h"
#include "SpotListener.h"
#include "MoveType.h"

/*
Spot represents an x,y Position on the Board. The Spot's attributes are 1) the Position of the Spot, 2) the id of the Box that is at the Position, or -1 if no Box is at that Position. 3) The MoveType of the possible Box (MoveType::left if there is no Box on the Position.) The Spot also keeps a list of listeners, which it updates when changeNote() is called and is successful.
*/
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

    /*
    Returns the current Box id and the MoveType at the Spot. If there is no Box, then returns MoveType::left and  -1 for the Box id. Note getBoardNote() is not thread safe. While this method is being called, the Spot may be changing, so the returned BoardNote may be incomplete or invalid.
    */
    BoardNote getBoardNote() const;

    /* Updates the Spot with the @boardNotes's boxId and MoveType.

    changeNote() is thread safe, only one thread can access this method at one time.

    The Spot only allows changes to the MoveType in the following order. Note when Spot is constructed it starts with a MoveType of MoveType::left reflecting no Box. The allowed order: MoveType::left, MoveType::to_arrive, MoveType::arrive, MoveType::to_leave, MoveType::left.
    
    If the Spot has a boxId of -1 and MoveType::left, then changeNote() will only be successful if @boardNote has MoveType::to_arrive. Any positive boxId is allowed. Any other MoveType will result in an exception.

    If the Spot has a boxId and a MoveType::to_arrive then only a BoardNote with a MoveType::arrive and the same boxId will be successful. A BoardNote with a different boxId and MoveType::to_arrive will be unsuccessful and return false. All other BoardNotes will throw an exception.

    If the Spot has a boxId and a MoveType::arrive then only a BoardNote with a MoveType::to_leave and the same boxId will be successful. A BoardNote with a different BoxId and MoveType::to_arrive will be unsuccessful and return false. All other BoardNotes will throw an exception.

    If the Spot has a boxId and a MoveType::to_leave then only a BoardNote with a MoveType::left and the same boxId will be successful. A BoardNote with a different boxId and MoveType::to_arrive will be unsuccessful and return false. All other BoardNotes will throw an exception.

    If an exception is not thrown, whether the call was successful or not, the original boxId will be returned. That is the boxId which is replaced if the call is successful or the boxId that was not replaced if the call is not successful.
    */
    std::pair<int, bool> changeNote(BoardNote note);

    void registerListener(SpotListener* listener);


    private:

    const Position _position;
    int _boxId = -1;
    MoveType _type = MoveType::left;
    mutable std::shared_mutex _mm;
    
    std::string _stateString = "-1, MoveType::left";

    std::string errorString(BoardNote incomingNote);
    
    void notifyListeners();

    std::vector<SpotListener*> _listeners{};

    void updateStateString();

};

#endif
