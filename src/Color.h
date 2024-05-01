#ifndef COLOR__H
#define COLOR__H

#include <vector>

/*
Color is essentially a vector of shades for a given color. Each shade has a red, green, and blue component. Users request the red, green, or blue component for a given shade.
*/
class Color
{

    public:
   
    /*
    @shades is a vector of shades. Each shade is a vector of size 3. The first int in the shade represents the red component, the 2nd int is the green component, and the last int is the blue component. As an example of a Color with two shades: shades = {vector<uint8_t>{0x00, 0x4D, 0x40}, vector<uint8_t>{0x00, 0x69, 0x5D}}. Neither shade has a red component, it's zero.
    */ 
    Color(std::vector<std::vector<uint8_t>> shades);
    Color() = delete;
    Color(const Color& o) = default;
    Color(Color&& o) noexcept = default;
    Color& operator=(const Color& o) = default;
    Color& operator=(Color&& o) noexcept = default;
    ~Color() noexcept = default; 
  
    uint8_t getRed(int level) const;
    uint8_t getGreen(int level) const;
    uint8_t getBlue(int level) const;

    int getNumberOfShades() const;


    private:

    std::vector<std::vector<uint8_t>> _shades{};
    int _numOfShades = -1;
    
};

#endif
    
