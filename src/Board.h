#ifndef BOARD__H
#define BOARD__H

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <utility>
#include <unordered_map>
#include <vector>

#include "BoardCallback.h"
#include "BoardListener.h"
#include "Box.h"
#include "BoxTaken.h"
#include "Drop.h"
#include "Position.h"
#include "Spot.h"

// Contains a matrix of Spots.
// Allows for changing spots with the addNote() method.
// Returns the spots that have been changed since the last time the changes were asked for.
// Returns the current boxId and type at a position on the board.

class Board
{
public:
    Board(int width, int height);
    Board(const Board& board) = delete;
    Board(Board&& o) noexcept = delete;
    Board& operator=(const Board& board) = delete;
    Board& operator=(Board&& o) noexcept = delete;
    ~Board() noexcept = default;

    int getWidth() const;
    int getHeight() const;

    bool addNote(Position position, BoardNote boardNote);
    void registerCallback(Position pos, BoardCallback& callBack);
    void registerListener(BoardListener* listener);
    void sendChanges();
    
    BoardNote getNoteAt(Position position) const;

private:
    int _width;
    int _height;
    
    // _spots is the master board.
    std::vector<std::vector<Spot>> _spots;

    // _dropMatrix1 and _dropMatrix2 boards keep track of the changes to the board that have not been sent out.
    std::vector<std::vector<Drop>> _dropMatrix1;
    std::vector<std::vector<Drop>> _dropMatrix2;
    
    // _receivingMatrix points to either _dropMatrix1 or _dropMatrix2. Changes are recorded in the matrix that _receivingMatrix currenlty points to. When sendChanges() is called, the matrix _receivingMatrix points to is toggled.
    std::vector<std::vector<Drop>>* _receivingMatrix = nullptr;

    std::vector<Box> _boxes;
    std::vector<Box> _boxesBuffer1;
    std::vector<Box> _boxesBuffer2;
    std::vector<Box>* _receivingBoxesBuffer = nullptr;

    std::vector<BoxTaken> _lastBox;

    // TODO these callbacks should be const
    std::unordered_map<Position, BoardCallback&> _boardCallbacksPerPos{};    
    std::unordered_set<BoardListener*> _listeners;
    
    mutable std::shared_mutex _mux;

    void toggleReceivingMatrix();
     
};

#endif

