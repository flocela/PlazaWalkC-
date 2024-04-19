#ifndef BOARD__H
#define BOARD__H

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <utility>
#include <unordered_map>
#include <vector>

#include "NoteSubscriber.h"
#include "BoardListener.h"
#include "Box.h"
#include "Drop.h"
#include "Position.h"
#include "Spot.h"

// Contains a matrix of Spots. X-direction is from left to right. Y-direction is from top to bottom. Spot at Position {2, 4} is over two to the right and down four from the origin.
// Allows for changing Spots with the addNote() method.
// Returns the Spots that have been changed since the last time the changes were asked for.
// Returns the current state of the Boxes specified in the constructor.
// Returns the current boxId and SpotType at a position on the Board.

class Board
{
public:
    
    Board(int width, int height, std::vector<Box>&& boxes);
    Board(const Board& board) = delete;
    Board(Board&& o) noexcept = delete;
    Board& operator=(const Board& board) = delete;
    Board& operator=(Board&& o) noexcept = delete;
    ~Board() noexcept = default;

    // Returns the sizes of the matrix.
    int getWidth() const;
    int getHeight() const;

    // BoardNote contains the BoxId and MovementType that will happen at this Position. If the movement is successful (See Spot's rules.) then this Position's Spot will contain the new BoardNote. If the movement is not successful (because another box is already at that position) then then the Spot does not change and both boxes' levels will go up by one. This symbolizing the incoming box running into the box standing at that Position.
    bool addNote(Position position, BoardNote boardNote);

    // Registers a NoteSubscriber at Position pos. When addNote is successful at pos, the registered NoteSubscriber is notified through its callback() method. 
    void registerNoteSubscriber(Position pos, NoteSubscriber& callBack);

    // Register a BoardListener. When requested (through sendChanges()) BoardListeners receive changes. See sendChanges() for more info on those sent changes.
    void registerListener(BoardListener* listener);

    // Sends 1) changes to Spots on Board and 2) the current state of the Boxes. Changes to Spots are in the form of an unordered_map<SpotType, unordered_set<Drop>>. This map only contains the changes since the last time sendChanges was called. The current state of the Boxes is in the form of an unordered_map<int, BoxInfo>. All Boxes are included, even Boxes that have not entered the Board yet or have been removed because they reached their final destination.
    void sendChanges();

    BoardNote getNoteAt(Position position) const;

private:
    const int _width;
    const int _height;
    
    // _spots is the master board.
    std::vector<std::vector<Spot>> _spots;

    // _dropMatrix1 and _dropMatrix2 keep track of the changes to the board that have not been sent out.
    std::vector<std::vector<Drop>> _dropMatrix1;
    std::vector<std::vector<Drop>> _dropMatrix2;
    
    // _receivingMatrix points to either _dropMatrix1 or _dropMatrix2. When sendChanges() is called the matrix that _receivingMatrix points to is toggled from _dropMatrix1 to _dropMatrix2 or vice versa.  Changes are recorded in the matrix that _receivingMatrix currenlty points to.
    std::vector<std::vector<Drop>>* _receivingMatrix = nullptr;

    // boxes per box id
    std::unordered_map<int, Box> _boxes{};

    std::unordered_map<Position, NoteSubscriber&> _noteSubscribersPerPos{};    
    std::unordered_set<BoardListener*> _listeners;
    
    mutable std::shared_mutex _mux;
    mutable std::shared_mutex _sendChangesMutex;
     
};

#endif

