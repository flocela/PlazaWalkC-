#ifndef SPOTLISTENER__H
#define SPOTLISTENER__H

#include <string>
#include <vector>

/*
Receives and saves state strings. The state string is the Spot's id and MoveType combined into a string.
*/
class SpotListener
{

public:

    void receiveStateString(std::string combinedString);

    std::vector<std::string> getStateStrings() const;

private:

    std::vector<std::string> _stateStrings{};

};

#endif
