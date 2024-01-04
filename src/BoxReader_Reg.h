#ifndef BOXREADER_REG__H
#define BOXREADER_REG__H

#include "Box.h"
#include "BoxReader.h"

class BoxReader_Reg : public BoxReader
{
public:
    BoxReader_Reg(const Box&);
    BoxReader_Reg() = delete;
    BoxReader_Reg(const BoxReader_Reg& o) = delete;
    BoxReader_Reg(BoxReader_Reg&& o) noexcept = delete;
    BoxReader_Reg& operator=(const BoxReader_Reg& o) = delete;
    BoxReader_Reg& operator=(BoxReader_Reg&& o) noexcept = delete;
    ~BoxReader_Reg() noexcept = default;

    int getId() const override;    
    int getWidth() const override;
    int getHeight() const override;

    Position getPos(std::chrono::time_point<std::chrono::high_resolution_clock> cutOffTime) const override;

    std::vector<BoxNote> getAllNotes() const override;
    std::vector<BoxNote> getLastNotes(int count) const override;

private:
    const Box& _box;
};

#endif
