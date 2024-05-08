#include "SpotListener.h"

using namespace std;

void SpotListener::receiveStateString(string combinedString)
{
    _stateStrings.push_back(combinedString);
}

vector<string> SpotListener::getStateStrings() const
{
    return _stateStrings;
}
