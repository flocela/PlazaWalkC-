#include "Spot.h"
#include <chrono>
#include <sstream>
#include <thread>

using namespace std;

Spot::Spot(Position pos):_position{pos}
{}

Spot::Spot(const Spot& o): _position{o._position}
{
    _boxId = o._boxId;
    _type = o._type;
}

Spot::Spot(Spot&& o)noexcept:_position{o._position}
{
    _boxId = o._boxId;
    _type = o._type;
}
    

Position Spot::getPosition() const
{
    return _position;
}

pair<int, bool> Spot::changeNote(BoardNote incomingNote)
{
    unique_lock<shared_mutex> lock(_mm);

    int incomingBoxId = incomingNote.getBoxId();
    MoveType incomingType  = incomingNote.getType();
    
    int origBoxId = _boxId;
    
    if (_type == MoveType::left)
    { 
        if (incomingType != MoveType::to_arrive)
        {   
            throw invalid_argument(errorString(incomingNote));
        }
        else
        {
            _boxId = incomingBoxId;
            _type = incomingType;
        }
    }
    else if (_type == MoveType::to_leave)
    {  
        if (incomingType == MoveType::to_arrive && incomingBoxId != _boxId)
        {
            return {_boxId, false};
        }
        else
        {
            if (_boxId == incomingBoxId && incomingType == MoveType::left)
            {
                _type = MoveType::left;
                _boxId = -1;
            }
            else
            {
                throw invalid_argument(errorString(incomingNote));
            }
        } 
    }
    else if (_type == MoveType::to_arrive)
    {  
        if (incomingType == MoveType::to_arrive && incomingBoxId != _boxId)
        {  
            return {_boxId, false};
        }
        else if (_boxId == incomingBoxId && incomingType == MoveType::arrive)
        {   
            _boxId = incomingBoxId;
            _type = incomingType;
        }
        else 
        {
            throw invalid_argument(errorString(incomingNote));
        } 
    }
    else if (_type == MoveType::arrive)
    {   
        if (incomingType == MoveType::to_arrive && incomingBoxId != _boxId)
        {
            return {_boxId, false};
        }
        else if (_boxId == incomingBoxId && incomingType == MoveType::to_leave)
        {
            _boxId = incomingBoxId;
            _type = incomingType;
        }
        else
        {
            throw invalid_argument(errorString(incomingNote));
        } 
    }
    
    notifyListeners();
    return {origBoxId, true};
}

BoardNote Spot::getBoardNote() const
{
    shared_lock<shared_mutex> lock(_mm);
    return BoardNote{_boxId, _type};
}

void Spot::updateStateString()
{
    stringstream ss;
    ss << "B" <<
          to_string(_boxId) <<
          ", " <<
          _type;
    _stateString = ss.str();
}

void Spot::registerListener(SpotListener* listener)
{
    _listeners.push_back(listener);
}

void Spot::notifyListeners()
{
    for(SpotListener* listener: _listeners)
    {
        updateStateString();
        listener->receiveStateString(_stateString);
    }
}

string Spot::errorString(BoardNote incomingNote)
{ 
    stringstream ss;
    ss << "At {" << to_string(_position.getX()) + ", " +
        to_string(_position.getY()) + "} "  +
        " can not accept the received BoardNote with boxId of " +
        to_string(incomingNote.getBoxId()) + " and type of "  +
        to_string(static_cast<int>(incomingNote.getType())) +
        ". Current boxId and type are " +
        to_string(_boxId) + " and " +
        to_string(static_cast<int>(_type)) + ".";
    return ss.str();
}

