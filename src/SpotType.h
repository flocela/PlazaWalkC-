#ifndef SPOT_TYPE__H
#define SPOT_TYPE__H

#include <iostream>

enum class SpotType{to_arrive, arrive, to_leave, left};

std::ostream& operator<<(std::ostream& os, SpotType const& obj);


#endif
