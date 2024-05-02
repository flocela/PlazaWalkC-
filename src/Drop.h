#ifndef DROP__H
#define DROP__H

#include "Position.h"
#include "SpotType.h"

/*
Drop is a container for a Position, a boxId, and SpotType. It also contains a has changed bool, so the user can mark it as having had changed, or not.
*/
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

    /*
    Two Drops are equal if they have the same Position.
    */
    bool operator== (const Drop& o) const;

    friend std::ostream& operator<< (std::ostream& o, const Drop& d)
    {
        std::string boolString = (d._changed) ? "true" : "false";
        o << "Drop: [{" << 
             std::to_string(d._position.getX()) << ", " << 
             std::to_string(d._position.getY()) << "}, " <<
             std::to_string(d._boxId) << ", " <<
             d._type << ", " <<
             boolString <<
             "]";
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
            // prime numbers
            int A = 32059; 
            int B = 117989;
            unsigned int h = 97;
            h = (h) ^ (d.getPosition().getX() * A);
            h = (h) ^ (d.getPosition().getY() * B);
            return h;
        }
    };
}

#endif
