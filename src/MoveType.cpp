#include "MoveType.h"

using namespace std;

ostream& operator<<(ostream& os, MoveType const& obj)
{ 
    string typeString{};
    switch(obj)
    {
        case MoveType::to_arrive:
            typeString = "MoveType::to_arrive";
            break;
        case MoveType::arrive:
            typeString = "MoveType::arrive";
            break;
        case MoveType::to_leave:
            typeString = "MoveType::to_leave";
            break;
        case MoveType::left:
            typeString = "MoveType::left";
            break;
        default:
            typeString = "unknown";
            break;
    }
    os << typeString;
    return os;
}
