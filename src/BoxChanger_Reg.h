#ifndef BOXCHANGER_REG__H
#define BOXCHANGER_REG__H

#include "Box.h"
#include "BoxChanger.h"

class BoxChanger_Reg : public BoxChanger
{
public:
    BoxChanger_Reg(Box& box);
    BoxChanger_Reg() = delete;
    BoxChanger_Reg(const BoxChanger_Reg& o) = delete;
    BoxChanger_Reg(BoxChanger_Reg&& o) noexcept = delete;
    BoxChanger_Reg& operator=(const BoxChanger_Reg& o) = delete;
    BoxChanger_Reg& operator=(BoxChanger_Reg&& o) noexcept = delete;
    ~BoxChanger_Reg() noexcept = default;

    void addNote(BoxNote note) override;

private:
    Box& _box;

};

#endif
    void addNote(BoxNote note);
