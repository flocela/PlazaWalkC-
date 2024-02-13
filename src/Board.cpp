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
    shared_lock<shared_mutex> lock(_mux);

    bool success = _spots[position.getY()][position.getX()].tagNote(boardNote);

    if (_boardCallbacksPerPos.find(position) != _boardCallbacksPerPos.end())
    {
        _boardCallbacksPerPos.at(position).callback(boardNote, position);
    }

    return success;
}

// TODO maybe delete this method if it isn't used.
BoardNote Board::getNoteAt(Position position) const
{
    unique_lock<shared_mutex> lock(_mux);
    return BoardNote{_spots[position.getY()][position.getX()].getBoxId(),
                     _spots[position.getY()][position.getX()].getType()};
}

void Board::registerCallback(Position pos, BoardCallback& callBack)
{
    _boardCallbacksPerPos.insert({pos, callBack});
}

void Board::sendChanges()
{
    unordered_map<Position, int> typePerPosition;
    {
        unique_lock<shared_mutex> lock(_mux);
        for (int ii=0; ii<_height; ++ii)
        {
            for (int jj=0; jj<_width; ++jj)
            {
                typePerPosition.insert({Position{ii, jj}, _spots[ii][jj].getType()});
            }
        }
    }
    
    for(Agent* agent : _agents)
    {   
        agent->receiveChanges(typePerPosition);
    }
}

void Board::registerAgent(Agent* agent)
{
    _agents.insert(agent);
}
        
