#include "Spot.h"
#include <iostream>
#include <chrono>
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
    SpotType incomingType  = incomingNote.getType();
    
    int origBoxId = _boxId;
    
    if (_type == SpotType::left)
    { 
        if (incomingType != SpotType::to_arrive)
        {   
            throw invalid_argument(errorString(incomingNote));
        }
        else
        {
            _boxId = incomingBoxId;
            _type = incomingType;
        }
    }
    else if (_type == SpotType::to_leave)
    {  
        if (incomingType == SpotType::to_arrive && incomingBoxId != _boxId)
        {
            return {_boxId, false};
        }
        else
        {
            if (_boxId == incomingBoxId && incomingType == SpotType::left)
            {
                _type = SpotType::left;
                _boxId = -1;
            }
            else
            {
                throw invalid_argument(errorString(incomingNote));
            }
        } 
    }
    else if (_type == SpotType::to_arrive)
    {  
        if (incomingType == SpotType::to_arrive && incomingBoxId != _boxId)
        {  
            return {_boxId, false};
        }
        else if (_boxId == incomingBoxId && incomingType == SpotType::arrive)
        {   
            _boxId = incomingBoxId;
            _type = incomingType;
        }
        else 
        {
            throw invalid_argument(errorString(incomingNote));
        } 
    }
    else if (_type == SpotType::arrive)
    {   
        if (incomingType == SpotType::to_arrive && incomingBoxId != _boxId)
        {
            return {_boxId, false};
        }
        else if (_boxId == incomingBoxId && incomingType == SpotType::to_leave)
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
        _stateString= "B";
        _stateString.append(to_string(_boxId));
        _stateString.append(",T");
        _stateString.append(to_string((int)(_type)));
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
        listener->receiveCombinedString(_stateString);
    }
}

string Spot::errorString(BoardNote incomingNote)
{ return "At {" + to_string(_position.getX()) + ", " + to_string(_position.getY()) + "} "  + " can not accept the received BoardNote with boxId of " + to_string(incomingNote.getBoxId()) + " and type of "  + to_string(static_cast<int>(incomingNote.getType())) + ". Current boxId and type are " + to_string(_boxId) + " and " + to_string(static_cast<int>(_type)) + ".";
}

