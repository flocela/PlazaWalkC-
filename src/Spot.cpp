#include "Spot.h"
#include <iostream>

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

bool Spot::tagNote(BoardNote note)
{
    unique_lock<shared_mutex> lock(_mm);
    int noteBoxId = note.getBoxId();
    int noteType  = note.getType();

    if (_type == -1)
    { 
        if (noteType != 2)
        {   //cout << errorString(note) << endl;
            throw invalid_argument(errorString(note));
        }
        else
        {
            _boxId = noteBoxId;
            _type = noteType;
            return true;
        }
    }
    else if (_type == 1)
    {  
        if (noteType == 2 && noteBoxId != _boxId)
        {
            return false;
        }
        else
        {
            if (_boxId == noteBoxId && noteType == 3)
            {
                _type = -1;
                _boxId = -1;
            }
            else
            {
                //cout << errorString(note) << endl;
                throw invalid_argument(errorString(note));
            }
        } 
    }
    else if (_type == 2)
    {  
        if (noteType == 2 && noteBoxId != _boxId)
        {  
            return false;
        }
        else if (_boxId == noteBoxId && noteType == 4)
        {   
            _boxId = noteBoxId;
            _type = noteType;
        }
        else 
        {
            throw invalid_argument(errorString(note));
        } 
    }
    else if (_type == 4)
    {   
        if (noteType == 2 && noteBoxId != _boxId)
        {
            return false;
        }
        else if (_boxId == noteBoxId && noteType == 1)
        {
            _boxId = noteBoxId;
            _type = noteType;
        }
        else
        {
            //cout << errorString(note) << endl;
            throw invalid_argument(errorString(note));
        } 
    }
    return true;
}

int Spot::getBoxId() const
{
    shared_lock<shared_mutex> lock(_mm);
    return _boxId;
}

int Spot::getType() const
{
    shared_lock<shared_mutex> lock(_mm);
    return _type;
}

string Spot::errorString(BoardNote boardNote)
{ return "At {" + to_string(_position.getX()) + ", " + to_string(_position.getY()) + "} "  + " can not accept the received BoardNote with boxId of " + to_string(boardNote.getBoxId()) + " and type of "  + to_string(boardNote.getType()) + ". Current boxId and type are " + to_string(_boxId) + " and " + to_string(_type) + ".";
}
    
