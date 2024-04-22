#ifndef BOX__H
#define BOX__H

#include <bitset>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <unordered_set>
#include <utility>

#include "BoxInfo.h"

class Box{

public:
    Box(int id, int group, int width, int height);
    Box() = default;
    Box(const Box& o); // TODO delete copy constructor and move constructor. Do I ever use them?
    Box(Box&& o) noexcept;
    Box& operator= (const Box& o) = delete;
    Box& operator= (Box&& o) noexcept = delete;
    ~Box() noexcept = default;

    void upLevel();

    // No reason to lock getId(), getGroupId(), getHeight(), getWidth() methods
    // with a shared_lock since _id, _groupid, _width, and _height are immutable.
    int getId() const;    
    int getGroupId() const;
    int getHeight() const;
    int getWidth() const;

    // getLevel() is protected with a unique_lock using mutex _mm. It can not be
    // called at the same time as getInfo(). No two threads can "enter" into 
    // getLevel() at the same time.
    int getLevel() const;

    // Contains a _shared_mutex with mutex _mm. Can not be called at the same time 
    // as getLevel().
    BoxInfo getInfo() const;
    
    bool operator== (const Box& o) const;

private:
    const int _id = -1;
    const int _groupid = -1;
    int _level  = 0;
    int _width  = -1; 
    int _height = -1;
    mutable std::shared_mutex _mm;
};

// TODO may need to update this with groupid
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
