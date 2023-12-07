#ifndef BOX__H
#define BOX__H

#include <bitset>
#include <utility>

class Box{

public:
    Box(int id, int width, int height, int xPos, int yPos);
    Box() = delete;
    Box(const Box& o) = default;
    Box(Box&& o) noexcept = default;
    Box& operator= (const Box& o) = default;
    Box& operator= (Box&& o) noexcept = default;
    ~Box() noexcept = default;

    int getId() const;    
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    void setX(int xPos);
    void setY(int yPos);
    void setHeight(int height);
    void setWidth(int width);

    bool operator== (const Box& o) const;

private:
    int _id = 0;
    int _width  = 0;// make this const
    int _height = 0; // make this const
    int _xPos   = 0; 
    int _yPos   = 0;    

};

namespace std
{
    template<>
    struct hash<Box>
    {
        size_t operator()(const Box& b) const
        {   return (
                     (
                       ( 
                         ( 
                           ( 
                             ( 
                             hash<int>()(b.getId()) ^ ( hash<int>()(b.getWidth()) << 1)
                             ) >> 1 
                           ) ^ (hash<int>()(b.getHeight()) << 1)
                         ) >> 1
                       ) ^ (hash<int>()(b.getX()) << 1)
                     ) >> 1
                   ) ^ (hash<int>()(b.getY()) << 1);
        }
    };
}

#endif
