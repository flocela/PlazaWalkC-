#include "BoxReader_Reg.h"

BoxReader_Reg::BoxReader_Reg(const Box& box): _box{box} {}

int BoxReader_Reg::getId() const
{
    return _box.getId();   
}    

int BoxReader_Reg::getWidth() const
{
    return _box.getWidth();
}

int BoxReader_Reg::getHeight() const 
{
    return _box.getHeight();
}

Position BoxReader_Reg::getPos(std::chrono::time_point<std::chrono::high_resolution_clock> cutOffTime) const 
{
    return _box.getPos(cutOffTime);
}

std::vector<BoxNote> BoxReader_Reg::getAllNotes() const
{
    return _box.getAllNotes();
}

std::vector<BoxNote> BoxReader_Reg::getLastNotes(int count) const
{
    return _box.getLastNotes(count);
}
