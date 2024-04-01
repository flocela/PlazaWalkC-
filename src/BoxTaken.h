#ifndef BOXTAKEN__H
#define BOXTAKEN__H

#include <mutex>
#include <shared_mutex>

class BoxTaken
{

public:
    BoxTaken() = default;
    BoxTaken(const BoxTaken& o);
    BoxTaken(BoxTaken&& o) noexcept;
    BoxTaken& operator= (const BoxTaken& o) = delete;
    BoxTaken& operator= (BoxTaken&& o) noexcept = delete;
    ~BoxTaken() noexcept = default;

    void changeToTrue();
    bool getState() const;

private:
    
    bool _state = false;
    mutable std::shared_mutex _mm;

};

#endif

