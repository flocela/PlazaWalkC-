#include "Board.h"
#include "BoardRecorderAgent.h"

using namespace std;

Board::Board(int width, int height)
:   _width{width},
    _height{height}
{
    for(int row=0; row<height; ++row)
    {
        vector<Spot> rowOfSpots{};
        for(int col=0; col<width; ++col)
        {
            rowOfSpots.push_back(Spot{Position(col, row)});
        }
        _spots.push_back(rowOfSpots);
    }
}

int Board::getWidth() const
{
    return _width;
}

int Board::getHeight() const
{
    return _height;
}

bool Board::addNote(Position position, BoardNote boardNote)
{
    bool success = _spots[position.getY()][position.getX()].tagNote(boardNote);

    if (_boardCallbacksPerPos.find(position) != _boardCallbacksPerPos.end())
    {
        _boardCallbacksPerPos.at(position).callback(boardNote, position);
    }

    return success;
}

BoardNote Board::getNoteAt(Position position) const
{
    return BoardNote{_spots[position.getY()][position.getX()].getBoxId(),
                     _spots[position.getY()][position.getX()].getType()};
}

void Board::registerCallback(Position pos, BoardCallback& callBack)
{
    _boardCallbacksPerPos.insert({pos, callBack});
}

void Board::sendChanges()
{
    for(BoardRecorderAgent* boardRecorderAgent : _boardRecorderAgents)
    {
        unordered_map<Position,int> typePerPosition{};
        boardRecorderAgent->receiveChanges(typePerPosition);
    }
}

void Board::registerBoardRecorderAgent(BoardRecorderAgent* boardRecorderAgent)
{
    _boardRecorderAgents.insert(boardRecorderAgent);
}
        
