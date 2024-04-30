#ifndef BOARD__H
#define BOARD__H

class BoardProxy;
#include <memory>
#include <shared_mutex>
#include <vector>
#include <unordered_map>

#include "BoardListener.h"
#include "BoardProxy.h"
#include "Box.h"
#include "Drop.h"
#include "NoteSubscriber.h"
#include "Position.h"
#include "Spot.h"

/*  
Conceptually a plane where Boxes are placed and can move in the x and y directions.

The Board class contains a matrix of Spots, and each Spot contains a Position that matches the Spot's x,y position on the Board. In the matrix of Spots's, x-direction runs from left to right. The y-direction runs from top to bottom. The origin is in the top left corner of the Board. A Spot at Position {2, 4} is over two to the right and down four from the origin.

When a Box is placed on the Board, removed from the Board, or moves along the Board, the Board keeps track of these movements by updating its matrix of Spots. Requests to Box movements on the Board are done through the addNote() method.

    The Board also keeps track of the Boxes and their state.
*/

class Board
{
    public:
    
    /*
    @boxes contains all the Boxes that Board will every be in charge of.
    */    
    Board(int width, int height, std::vector<Box>&& boxes);

    Board(const Board& board) = delete;
    Board(Board&& o) noexcept = delete;
    Board& operator=(const Board& board) = delete;
    Board& operator=(Board&& o) noexcept = delete;
    ~Board() noexcept = default;

    int getWidth() const;
    int getHeight() const;
    
    BoardProxy getBoardProxy();

    /*  
    @position is the Position that is being requested to be updated.

    @boardNote contains the boxId and SpotType that the Spot at @position should be updated to.

    If the movement is successful (See Spot's rules.) then the Spot at @positiont will contain the new BoardNote. If the movement is not successful (say because another box is already at that position) then the Spot does not change and both boxes' levels will go up by one. This symbolizing the incoming box running into the box standing at @position.
    */
    bool addNote(Position position, BoardNote boardNote);


    /*
    Registers a NoteSubscriber for Position @pos. When the addNote() method is successful at @pos, the registered NoteSubscriber is notified through its callback() method. 
    */
    void registerNoteSubscriber(Position pos, NoteSubscriber& callBack);

    /*
    Register a BoardListener. BoardListeners receive updates sendChanges() is called. See sendChanges() for more info on those sent changes.
    */
    void registerListener(BoardListener* listener);

    /*
    Sends 1) the current state of the Boxes and 2) changes to the Spots. The current state of the Boxes is in the form of an unordered_map<int, BoxInfo> of boxIds to Boxes. All Boxes are included, even Boxes that have not entered the Board yet or have been removed because they reached their final destination. Changes to Spots are in the form of an unordered_set of Drops. This set contains only the changes since the last time sendStateAndChanges() was called.
    */
    void sendStateAndChanges();

    BoardNote getNoteAt(Position position) const;

private:
    const int _width;
    const int _height;
    
    /*
    _spots is the master board.
    */
    std::vector<std::vector<Spot>> _spots;

    /*
    _dropMatrix1 and _dropMatrix2 keep track of the changes to the board that have not been sent out.
    */
    std::vector<std::vector<Drop>> _dropMatrix1;
    std::vector<std::vector<Drop>> _dropMatrix2;
    
    /*_receivingMatrix points to either _dropMatrix1 or _dropMatrix2. When sendChanges() is called the matrix that _receivingMatrix points to is toggled from _dropMatrix1 to _dropMatrix2 or vice versa.  Changes are recorded in the matrix that _receivingMatrix currenlty points to.
    */
    std::vector<std::vector<Drop>>* _receivingMatrix = nullptr;

    /*
    boxes per boxId
    */
    std::unordered_map<int, Box> _boxes{};

    std::unordered_map<Position, NoteSubscriber&> _noteSubscribersPerPos{};

    std::unordered_set<BoardListener*> _listeners;
    
    mutable std::shared_mutex _mux;
    mutable std::shared_mutex _sendChangesMutex;
     
};

#endif

