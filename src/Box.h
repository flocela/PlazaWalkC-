#ifndef BOX__H
#define BOX__H

#include <bitset>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <utility>

#include "BoxNote.h"

class Box{

public:
    Box(int id, int width, int height);
    Box() = delete;
    Box(const Box& o) = delete;
    Box(Box&& o) noexcept = delete;
    Box& operator= (const Box& o) = delete;
    Box& operator= (Box&& o) noexcept = delete;
    ~Box() noexcept = default;

    int getId() const;    
    int getWidth() const;
    int getHeight() const;

    Position getPos(std::chrono::time_point<std::chrono::high_resolution_clock> cutOffTime) const;

    void addNote(BoxNote note);

    std::vector<BoxNote> getAllNotes() const;
    std::vector<BoxNote> getLastNotes(int count) const;
    
    bool operator== (const Box& o) const;

private:
    int _id = 0;
    int _width  = 0; // make this const
    int _height = 0; // make this const
    std::vector<BoxNote> _notes{};
    
    mutable std::shared_mutex _mux;
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
