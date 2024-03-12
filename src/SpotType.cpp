#include "SpotType.h"

using namespace std;

ostream& operator<<(ostream& os, SpotType const& obj)
{
    string typeString{};
    switch(obj)
    {
        case SpotType::to_arrive:
            typeString = "to_arrive";
            break;
        case SpotType::arrive:
            typeString = "arrive";
            break;
        case SpotType::to_leave:
            typeString = "to_leave";
            break;
        case SpotType::left:
            typeString = "left";
            break;
        default:
            typeString = "unknown";
            break;
    }
    os << typeString;
    return os;
}
