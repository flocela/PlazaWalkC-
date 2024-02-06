#include "Spot.h"
#include <iostream>

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
        {   cout << errorString(note) << endl;
            throw invalid_argument(errorString(note));
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
        else
        {
            if (_boxId == noteBoxId && noteType == 3)
            {
                _type = -1;
                _boxId = -1;
            }
            else
            {
                cout << errorString(note) << endl;
                throw invalid_argument(errorString(note));
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
            cout << errorString(note) << endl;
            throw invalid_argument(errorString(note));
        } 
        else if (noteType != 4)
        { 
            cout << errorString(note) << endl;
            throw invalid_argument(errorString(note));
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
            cout << errorString(note) << endl;
            throw invalid_argument(errorString(note));
        } 
        else if (noteType != 1)
        {
            cout << errorString(note) << endl;
            throw invalid_argument(errorString(note));
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

string Spot::errorString(BoardNote boardNote)
{ return "At {" + to_string(_position.getX()) + ", " + to_string(_position.getY()) + "} "  + " can not accept the received BoardNote with boxId of " + to_string(boardNote.getBoxId()) + " and type of "  + to_string(boardNote.getType()) + ". Current boxId and type are " + to_string(_boxId) + " and " + to_string(_type) + ".";
}
    
