#include "BoxChanger_Reg.h"

BoxChanger_Reg::BoxChanger_Reg(Box& box):_box{box} {}

void BoxChanger_Reg::addNote(BoxNote note)
{
    _box.addNote(note);
}
