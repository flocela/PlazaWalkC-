#include "SpotListener.h"

using namespace std;

void SpotListener::receiveCombinedString(string combinedString)
{
    _combinedStrings.push_back(combinedString);
}

vector<string> SpotListener::getCombinedStrings() const
{
    return _combinedStrings;
}
