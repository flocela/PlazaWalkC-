#include "BoxListener.h"

using namespace std;

void BoxListener::receiveCombinedString(string combinedString)
{
    _combinedStrings.push_back(combinedString);
}

vector<string> BoxListener::getCombinedStrings() const
{
    return _combinedStrings;
}
