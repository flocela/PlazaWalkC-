#ifndef DROP__H
#define DROP__H

#include "Position.h"
#include "SpotType.h"

class Drop
{
    public:
    Drop(int x, int y);
    Drop(int x, int y, int boxId, SpotType type);
    Drop() = delete;
    Drop(const Drop& o) = default;
    Drop(Drop&& o) noexcept = default;
    Drop& operator=(const Drop& o) = delete;
    Drop& operator=(Drop&& o) noexcept  = delete;
    ~Drop() noexcept = default;

    void setBoxId(int id);
    void setSpotType(SpotType type);
    void setHasChanged(bool hasChanged);

    Position getPosition() const;
    int getBoxId() const;
    SpotType getSpotType() const;
    bool hasChanged() const;

    bool operator== (const Drop& o) const;
    friend std::ostream& operator<< (std::ostream& o, const Drop& d)
    {
        o << "Drop: [" + std::to_string(d._position.getX()) + ", " + std::to_string(d._position.getY()) << "]";
        return o;
    }

    private:
    Position _position;
    int _boxId = -1;
    SpotType _type = SpotType::left;
    bool _changed = false;

};

namespace std
{
    template<>
    struct hash<Drop>
    {
        size_t operator()(const Drop& d) const
        {
            return ( hash<int>()(d.getPosition().getX()) ^ (hash<int>()(d.getPosition().getY()) << 1) );
        }
    };
}

#endif
