#ifndef BOXLISTENER__H
#define BOXLISTENER__H

#include <string>
#include <vector>

class BoxListener
{

public:

    void receiveCombinedString(std::string combinedString);

    std::vector<std::string> getCombinedStrings() const;

private:

    std::vector<std::string> _combinedStrings{};

};

#endif
