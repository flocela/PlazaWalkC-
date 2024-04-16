#ifndef BOXINFO__H
#define BOXINFO__H

#include <bitset>
#include <shared_mutex>
#include <vector>
#include <unordered_set>
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
            vector<int> v= {b.getId(), b.getGroupId(), b.getLevel(), b.getWidth(), b.getHeight()};
            return hh(v, 0);
        }

        size_t hh(vector<int> v, int idx) const
        {
            if(idx == static_cast<int>(v.size()-1))
            {
                return hash<int>()(v[idx]);
            }
            else
            {
                return (
                        ((hash<int>()(v[idx])) ^ hh(v, idx+1))>>1
                       );
            }
        }
    };
}

#endif
