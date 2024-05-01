#include "Color.h"

using namespace std;

Color::Color(vector<vector<uint8_t>> shades): _shades{shades}, _numOfShades{static_cast<int>(shades.size())}
{}

uint8_t Color::getRed(int level) const
{
    if (level > static_cast<int>(_shades.size()))
    {
        return _shades[_shades.size()-1][0];
    }
    return _shades[level][0];
}

uint8_t Color::getGreen(int level) const
{
    if (level > static_cast<int>(_shades.size()))
    {
        return _shades[_shades.size()-1][1];
    }
    return _shades[level][1];
}

uint8_t Color::getBlue(int level) const
{
    if (level > static_cast<int>(_shades.size()))
    {
        return _shades[_shades.size()-1][2];
    }
    return _shades[level][2];
}

int Color::getNumberOfShades() const
{
    return _numOfShades;
}
