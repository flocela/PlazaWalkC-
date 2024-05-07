#ifndef BOX__H
#define BOX__H

#include <shared_mutex>

#include "BoxInfo.h"


class Box{

    public:

    Box(int id, int group, int width, int height);
    Box() = default;
    Box(const Box& o);
    Box(Box&& o) noexcept;
    Box& operator= (const Box& o) = delete;
    Box& operator= (Box&& o) noexcept = delete;
    ~Box() noexcept = default;

    /* No reason to lock getId(), getGroupId(), getHeight(), getWidth() methods with a shared_lock since _id, _groupid, _width, and _height are immutable.
    */
    int getId() const;    
    int getGroupId() const;
    int getHeight() const;
    int getWidth() const;

    /* getLevel() is protected with a shared_lock using mutex _mm. It can be called at the same time as getInfo(). It can not be called at the same time as upLevel().
    */
    int getLevel() const;

    /* getInfo() is protected with a shared_lock using mutex _mm. It can be called at the same time as getLevel(). It can not be called at the same time as upLevel().
    */
    BoxInfo getInfo() const;

    /* upLevel() is protected with a unique_lock using mutex _mm. It can not be accessed by two threads at the same time. It can not be accessed as the same time as getLevel() or getInfo().
    */
    void upLevel();
    
    bool operator== (const Box& o) const;


    private:

    const int _id = -1;
    const int _groupid = -1;
    int _level  = 0;
    int _width  = -1; 
    int _height = -1;
    mutable std::shared_mutex _mm;
};


namespace std
{
    template<>
    struct hash<Box>
    {
        size_t operator()(const Box& b) const
        {
            // prime numbers
            int A = 32059; 
            int B = 54059;
            int C = 76963;
            int D = 86969;
            unsigned int h = 97;
            h = (h) ^ (b.getId() * A);
            h = (h) ^ (b.getGroupId() * B);
            h = (h) ^ (b.getWidth() * C);
            h = (h) ^ (b.getHeight() * D);
            return h;
        }
    };
}

#endif
