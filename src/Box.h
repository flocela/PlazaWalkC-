#ifndef BOX__H
#define BOX__H

class Box{

public:
    Box(int id, int height, int width, int xPos, int yPos);
    Box() = delete;
    Box(const Box& o) = default;
    Box(Box&& o) noexcept = default;
    Box& operator= (const Box& o) = default;
    Box& operator= (Box&& o) noexcept = default;
    ~Box() noexcept = default;

    int getId() const;    
    int getX() const;
    int getY() const;
    int getHeight() const;
    int getWidth() const;
    void setX(int xPos);
    void setY(int yPos);
    void setHeight(int height);
    void setWidth(int width);

private:
    int _id = 0;
    int _height = 0;
    int _width  = 0;
    int _xPos   = 0;
    int _yPos   = 0;    

};

#endif
