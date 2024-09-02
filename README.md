# Plaza Walk
Click below to check out the [youtube video](https://www.youtube.com/watch?v=clG0zYToX9M)!

[![clG0zYToX9M](https://img.youtube.com/vi/clG0zYToX9M/0.jpg)](https://www.youtube.com/watch?v=clG0zYToX9M)
## Introduction

A simulation of people walking across a plaza, where each person is represented by a colored box. The boxes move concurrently, and each box has its own destination, path finder, and risk assessor. (A risky box may try to move into a position that is occupied, speculating that the current occupant will be leaving soon. Another, safer box would think this move is too risky to attempt.) If one box tries to enter the position of another box, then both boxes turn a darker shade. This represents two people bumping into each other.

## Code Explanation

### Code Introduction

See UML diagrams at [UML Diagrams](UMLDiagrams.pdf).

The plaza is represented by the [Board class](src/Board.h). It is conceptually a rectangle with positions in the x-y directions, but it also contains the state of the positions and Boxes on the Board.

A [Box](src/Box.h) may stand at any one position or may occupy two positions while it is in the process of moving from one position to the next. Each of the Board's positions has a [Spot](src/Spot.h) that records which Box is at that position (or no Box) and the Box's [MoveType](src/MoveType.h). (MoveTypes for a Box are: about to arrive, arrived, about to leave, or left a position.) Spots are stationary (they are assigned an x-y coordinate on the Board).

[main](src/main.cpp#L121) creates a vector of threads, each containing a Board reference and a unique Box id. Each thread is passed the same [function](src/Threader.cpp) that iteratively asks the Board to move its particular Box to a new position. The Board allows for multiple Spots to be updated at once. The Spot class does not allow two threads to update a Spot concurrently.

Once the threads are created and running, main's primary thread iteratively requests for the Board to broadcast its state (the state of the Boxes and their positions). The information from each broadcast is ultimately received by a Printer and the Printer renders the Board with its Boxes.

Internally the Board pauses all Board changes (Box movements) while it prepares the data for the broadcast. Once the data is collected, it accepts changes while broadcasting out the data. So the received data (received by the Printer) is always a tiny bit stale.

### Spot Records The Box's Move Type

As a Box moves from one position to the next, the Spots update their Box ids and MoveType attributes. All Spots start with a Box id of -1 and a MoveType::left (meaning the Spot is empty). When a Box steps onto a Spot, the Spot's Box id and MoveType are updated.  A Spot will only change the MoveType in this logical order: MoveType::left, MoveType::to_arrive, MoveType::arrive, MoveType::to_leave, MoveType::left. The following is an example of 2 Spots, where Box1 arrives at Old Spot and then moves to New Spot. Notice during the transition both Spots have the same Box id of 1 at the same time.
<pre><code>
Old Spot                            New Spot
Box -1 with MoveType::left          Box -1 with MoveType::left
Box  1 with MoveType::to_arrive     Box -1 with MoveType::left 
Box  1 with MoveType::arrive        Box -1 with MoveType::left
Box  1 with MoveType::arrive        Box  1 with MoveType::to_arrive
Box  1 with MoveType::to_leave      Box  1 with MoveType::to_arrive
Box  1 with MoveType::to_leave      Box  1 with MoveType::arrive
Box -1 with MoveType::left          Box  1 with MoveType::arrive
</code></pre>

Every thread contains one Mover. Every Mover contains one unique box id, and all Movers update Spots according to the correct specified order.

Spot has a unique_lock on its update method, so only one thread can update a Spot at any one time.

Once a thread (with a unique box id) changes a Spot from MoveType::left to MoveType::to_arrive, the Spot is essentially owned by that thread. The Spot contains the thread's unique box id. Other threads trying to enter the Spot with a MoveType::to_arrive will not be allowed to update the Spot. The Spot will return false because the received box id is different from the owning thread's box id.

Other threads must wait for the owning thread to issue the MoveTypes MoveType::arrive through MoveType::left before their requests are successful. It is not until the owning thread issues a request with MoveType::left, that another thread will be able to update that Spot. 

If a Spot containing a particular box id receives a request to update with another box id and a MoveType other than MoveType::to_arrive, then Spot throws an exception, and the program terminates. (Something has gone wrong if a thread is issuing a request other than MoveType::to_arrive at an occupied position. This suggests the thread believes its particular Box is already at that position.) This doesn't happen because of the locking in Spot's methods and Mover's adherence to the correct MoveType order.

### Choosing The Box's New Positions

The thread function's parameters include a Board reference, a Position Manager, a Decider, and a Mover.

The function contains a loop that only ends when the user closes the window or when the Box reaches its final position.

In the loop, the PositionManager returns a vector of suggested Positions.  The Decider chooses a position from the vector based on the Positions' MoveTypes. (The Decider gets the MoveTypes from the Board.) Then the Mover requests that the Board move the Box to that chosen position. This involves calling Board's changeSpot() method with the Mover's box id and the correct MoveTypes in the correct order. Once the Board moves the Box to the new position, the loop iterates again asking the PositionManager for a vector of possible, new positions.

It may be that the Mover's first call to changeSpot() with the parameter MoveType::to_arrive returns false. The Board is returning false to notify the caller that the Position is occupied. The Decider may have chosen the new position because a call to the Board at that time returned that the Spot was empty. Since the time the Board returned that the position was empty to the time the Mover tried to move the Box, the Spot may have become occupied. It may also have been that the Decider chose a Position it believed would become unoccupied by the time the Mover moved the Box there, but it in fact did not become vacant in time.

At every iteration the PositionManager is asked if the Box is at its end position. If it is, the loop ends and the Box is removed from the Board. The thread function ends.

### Tests

Using Catch2 for testsing. Tests can be found at [PlazaWalkCCode/tests/](tests/).

## License
Plaza Walk was completed in 2024 by Aurea F. Maldonado.

The code that allows rendering of text and blocks on a window is by Amine Ben Hassouna and can be found at https://github.com/aminosbh/sdl2-ttf-sample/blob/master/src/main.c.

Music for README video is from Kevin MacLeod. 
"Wallpaper" Kevin MacLeod (incompetech.com)
Licensed under Creative Commons: By Attribution 4.0 License
http://creativecommons.org/licenses/by/4.0/

I am using the same copyright as Amine Ben Hassouna.

This project is distributed under the terms of the [MIT license](LICENSE).

## Build Instructions

### Dependencies

- [Git][]
- C Compiler (gcc, ...)
- [CMake][]
- [SDL2][SDL] library
- [SDL2_ttf][] library

### Clone This Repo

In a folder, clone the repository. This will create the PlazaWalkCCode folder.

```sh

git clone git@github.com:flocela/PlazaWalkCCode.git
```

### Make the code

Create a build folder inside of the PlazaWalkCCode folder. In the PlazaWalkCCode/build folder type:
```sh
cmake .. && make
```

## Run The Project

In the build folder type

```sh
.sdl2-ttf-sample
```

## Run The Tests

In the build folder type
```sh
./RunTests
```



[SDL]: https://www.libsdl.org
[CMake]: https://cmake.org
[Git]: https://git-scm.com
[SDL2_image]: https://www.libsdl.org/projects/SDL_image
[SDL2_ttf]: https://www.libsdl.org/projects/SDL_ttf
