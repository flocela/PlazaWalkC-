#ifndef BOXINFO__H
#define BOXINFO__H

#include <utility>

class BoxInfo{

public:
    BoxInfo(int id, int group, int width, int height, int level);
    BoxInfo(const BoxInfo& o) = default;
    BoxInfo(BoxInfo&& o) noexcept = default;
    BoxInfo& operator=(const BoxInfo& o) = delete;
    BoxInfo& operator=(BoxInfo&& o) noexcept = delete;
    ~BoxInfo() = default;    

    int getId() const;    
    int getGroupId() const;
    int getWidth() const;
    int getHeight() const;
    int getLevel() const;
    
    bool operator== (const BoxInfo& o) const;

private:
    const int _id = -1;
    const int _groupid = -1;
    const int _width  = -1; 
    const int _height = -1;
    const int _level  = 0;
};

namespace std
{
    template<>
    struct hash<BoxInfo>
    {
        size_t operator()(const BoxInfo& b) const
        {
            // prime numbers
            int A = 21859;
            int B = 32059; 
            int C = 54059;
            int D = 76963;
            int E = 86969;
            
            unsigned int h = 97;
            h = (h) ^ (b.getId() * A);
            h = (h) ^ (b.getGroupId() * B);
            h = (h) ^ (b.getWidth() * C);
            h = (h) ^ (b.getHeight() * D);
            h = (h) ^ (b.getLevel() * E);
            return h;
        }
    };
}

#endif
