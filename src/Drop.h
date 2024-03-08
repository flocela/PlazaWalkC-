#ifndef DROP__H
#define DROP__H

#include "Position.h"

class Drop
{
public:
    Drop(int x, int y);
    Drop() = delete;
    Drop(const Drop& o) = default;
    Drop(Drop&& o) noexcept = default;
    Drop& operator=(const Drop& o) = default;
    Drop& operator=(Drop&& o) noexcept  = default;
    ~Drop() noexcept = default;

    Position _position;
    int _boxId = -1;
    int _type = -1;
    bool _changed = false;

    bool operator== (const Drop& o) const;
    friend std::ostream& operator<< (std::ostream& o, const Drop& d)
    {
        o << "Drop: [" + std::to_string(d._position.getX()) + ", " + std::to_string(d._position.getY()) << "]";
        return o;
    }
};

namespace std
{
    template<>
    struct hash<Drop>
    {
        size_t operator()(const Drop& d) const
        {
            return ( hash<int>()(d._position.getX()) ^ (hash<int>()(d._position.getY()) << 1) );
        }
    };
}

#endif
