#ifndef SPOTLISTENER__H
#define SPOTLISTENER__H

#include <string>
#include <vector>

class SpotListener
{

public:

    void receiveCombinedString(std::string combinedString);

    std::vector<std::string> getCombinedStrings() const;

private:

    std::vector<std::string> _combinedStrings{};

};

#endif
