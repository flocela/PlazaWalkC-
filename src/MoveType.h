#ifndef MOVE_TYPE__H
#define MOVE_TYPE__H

#include <iostream>

/*
MoveType::to_arrive means the Box has not arrived at the Spot, but will soon arrive.
MoveType::arrive means the Box has arrived at the Spot.
MoveType::to_leave means the Box will soon leave the Spot.
MoveType::left means the Box is no longer on this Spot.
*/
enum class MoveType{to_arrive=1, arrive=2, to_leave=3, left=4};

/*
Prints out the MoveType for example as "MoveType::left"
*/
std::ostream& operator<<(std::ostream& os, MoveType const& obj);


#endif
