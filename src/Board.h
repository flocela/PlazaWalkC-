#ifndef FLOBOARD__H
#define FLOBOARD__H

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <utility>
#include <unordered_map>
#include <vector>

#include "BoardCallback.h"
#include "BoardListener.h"
#include "Box.h"
#include "Drop.h"
#include "Position.h"
#include "Spot.h"

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
    BoardNote getNoteAt(Position position) const;
    void registerCallback(Position pos, BoardCallback& callBack);
    void registerListener(BoardListener* listener);
    void sendChanges();

private:
    int _width;
    int _height;
    
    // this is the master board.
    std::vector<std::vector<Spot>> _spots;

    // these boards keep track of the changes to the board that have not been sent out
    std::vector<std::vector<Drop>> _dropBoard1;
    std::vector<std::vector<Drop>> _dropBoard2;
    int _curDropBoard = 1;

    // TODO these callbacks should be const
    std::unordered_map<Position, BoardCallback&> _boardCallbacksPerPos{};    
    std::unordered_set<BoardListener*> _listeners;
    
    mutable std::shared_mutex _mux;
     
};

#endif

