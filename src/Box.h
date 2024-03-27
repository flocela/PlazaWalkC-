#ifndef BOX__H
#define BOX__H

#include <bitset>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <unordered_set>
#include <utility>

class Box{

public:
    Box(int id, int width, int height);
    Box() = delete;
    Box(const Box& o);
    Box(Box&& o) noexcept;
    Box& operator= (const Box& o) = delete;
    Box& operator= (Box&& o) noexcept = delete;
    ~Box() noexcept = default;

    void upLevel();

    int getId() const;    
    int getWidth() const;
    int getHeight() const;
    int getLevel() const;
    
    bool operator== (const Box& o) const;

private:
    int _id    = 0;
    int _level = 0;
    int _width = 0; // make this const
    int _height = 0; // make this const
    mutable std::shared_mutex _mm;
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
                         hash<int>()(b.getId()) ^ ( hash<int>()(b.getWidth()) << 1)
                         ) >> 1 
                       ) ^ (hash<int>()(b.getHeight()) << 1)
                     ) >> 1);
        }
    };
}

#endif
