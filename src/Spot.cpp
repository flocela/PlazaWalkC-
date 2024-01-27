#include "Spot.h"

using namespace std;

Spot::Spot(Position pos):_position{pos}
{}

Position Spot::getPosition() const
{
    return _position;
}

bool Spot::tagNote(BoardNote note)
{
    int noteBoxId = note.getBoxId();
    int noteType  = note.getType();

    if (_type == -1)
    { 
        if (noteType != 2)
        {
            throw invalid_argument("Can not accept the received BoardNote with boxId of " + to_string(noteBoxId) + " and type of "  + to_string(noteType) + ". Current boxId and type are " + to_string(_boxId) + " and " + to_string(_type) + ".");
        }
        else
        {
            _boxId = noteBoxId;
            _type = noteType;
            return true;
        }
    }
    if (_type == 1)
    {  
        if (noteType == 2 && noteBoxId != _boxId)
        {
            return false;
        } 
        else if (noteType != 3)
        {
            throw invalid_argument("Can not accept the received BoardNote with boxId of " + to_string(noteBoxId) + " and type of "  + to_string(noteType) + ". Current boxId and type are " + to_string(_boxId) + " and " + to_string(_type) + ".");
        }
        else
        {
            if (_boxId == noteBoxId)
            {
                _boxId = -1;
                _type = -1;
                return true;
            }
            else
            {
                throw invalid_argument("Can not accept the received BoardNote with boxId of " + to_string(noteBoxId) + " and type of "  + to_string(noteType) + ". Current boxId and type are " + to_string(_boxId) + " and " + to_string(_type) + ".");
            }
        }
    }
    if (_type == 2)
    {   
        if (noteType == 2 && noteBoxId != _boxId)
        {
            return false;
        }
        else if (_boxId != noteBoxId)
        {
            throw invalid_argument("Can not accept the received BoardNote with boxId of " + to_string(noteBoxId) + " and type of "  + to_string(noteType) + ". Current boxId and type are " + to_string(_boxId) + " and " + to_string(_type) + ".");
        } 
        else if (noteType != 4)
        {
            throw invalid_argument("Can not accept the received BoardNote with boxId of " + to_string(noteBoxId) + " and type of "  + to_string(noteType) + ". Current boxId and type are " + to_string(_boxId) + " and " + to_string(_type) + ".");
        }
        else
        {
            _boxId = noteBoxId;
            _type = noteType;
            return true;
        }
    }
    if (_type == 4)
    {   
        if (noteType == 2 && noteBoxId != _boxId)
        {
            return false;
        }
        else if (_boxId != noteBoxId)
        {
            throw invalid_argument("Can not accept the received BoardNote with boxId of " + to_string(noteBoxId) + " and type of "  + to_string(noteType) + ". Current boxId and type are " + to_string(_boxId) + " and " + to_string(_type) + ".");
        } 
        else if (noteType != 1)
        {
            throw invalid_argument("Can not accept the received BoardNote with boxId of " + to_string(noteBoxId) + " and type of "  + to_string(noteType) + ". Current boxId and type are " + to_string(_boxId) + " and " + to_string(_type) + ".");
        }
        else
        {
            _boxId = noteBoxId;
            _type = noteType;
            return true;
        }
    }
    return true;
}

int Spot::getBoxId() const
{
    return _boxId;
}

int Spot::getType() const
{
    return _type;
}


