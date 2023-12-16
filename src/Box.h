#ifndef BOX__H
#define BOX__H

#include <bitset>
#include <vector>
#include <utility>

#include "BoxNote.h"

class Box{

public:
    Box(int id, int width, int height);
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
    void setHeight(int height);
    void setWidth(int width);

    void addNote(BoxNote note);

    std::vector<BoxNote> getAllNotes() const;
    std::vector<BoxNote> getLastNotes(int count) const;
    
    bool operator== (const Box& o) const;

private:
    int _id = 0;
    int _width  = 0; // make this const
    int _height = 0; // make this const
    std::vector<BoxNote> _notes{};
    

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
