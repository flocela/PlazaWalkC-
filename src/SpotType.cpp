#include "SpotType.h"

using namespace std;

ostream& operator<<(ostream& os, SpotType const& obj)
{
    string typeString{};
    switch(obj)
    {
        case SpotType::to_arrive:
            typeString = "SpotType::to_arrive";
            break;
        case SpotType::arrive:
            typeString = "SpotType::arrive";
            break;
        case SpotType::to_leave:
            typeString = "SpotType::to_leave";
            break;
        case SpotType::left:
            typeString = "SpotType::left";
            break;
        default:
            typeString = "unknown";
            break;
    }
    os << typeString;
    return os;
}
