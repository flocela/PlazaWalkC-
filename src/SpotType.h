#ifndef SPOT_TYPE__H
#define SPOT_TYPE__H

#include <iostream>

enum class SpotType{to_arrive=1, arrive=2, to_leave=3, left=4};

std::ostream& operator<<(std::ostream& os, SpotType const& obj);


#endif
