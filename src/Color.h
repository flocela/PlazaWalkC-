#ifndef COLOR__H
#define COLOR__H

#include <vector>

class Color
{

    public:
    
    Color(std::vector<std::vector<uint8_t>> shades);
    Color() = delete;
    Color(const Color& o) = default;
    Color(Color&& o) noexcept = default;
    Color& operator=(const Color& o) = default;
    Color& operator=(Color&& o) noexcept = default;
    ~Color() noexcept = default; 
  
    // Returns the red/green/blue portion of the color for this level. If the level is larger than the number of shades this Color contains, then the red/green/blue portion of the last shade is returned. 
    uint8_t getRed(int level) const;
    uint8_t getGreen(int level) const;
    uint8_t getBlue(int level) const;

    int getNumberOfShades() const;



    private:

    std::vector<std::vector<uint8_t>> _shades{};
    int _numOfShades = -1;
    
};

#endif
    
