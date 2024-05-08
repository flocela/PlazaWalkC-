#ifndef SPOT_TYPE__H
#define SPOT_TYPE__H

#include <iostream>

/*
SpotType::to_arrive means the Box has not arrived at the Spot, but will soon arrive.
SpotType::arrive means the Box has arrived at the Spot.
SpotType::to_leave means the Box will soon leave the Spot.
SpotType::left means the Box is no longer on this Spot.
*/
enum class SpotType{to_arrive=1, arrive=2, to_leave=3, left=4};

/*
Prints out the SpotType for example as "SpotType::left"
*/
std::ostream& operator<<(std::ostream& os, SpotType const& obj);


#endif
