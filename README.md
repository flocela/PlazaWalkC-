# Across The Plaza 

https://github.com/flocela/PlazaWalkCCode/assets/4298622/c6445efa-8f78-4b5d-98b1-78eb97eb2487

A simulation of people walking across a plaza, where each person is represented by a colored box. Each box is in its own thread. Each Box has its own final destination and its own risk assesment. (A box may try to move into a position that is occupied speculating that the current occupant will be leaving soon, where as another box would think this move is too risky to attempt.) If one box tries to enter the position of another box, then both boxes turn a darker shade. This represents two people bumping into each other.

## Code Explanation

### Introduction To The Code 

See UML diagrams at AcrossThePlaza/UMLDiagrams.pdf.

The plaza is represented by the Board class. It is conceptually a rectangle with positions in the x-y directions, but also the class containing the state of the positions and Boxes on the Board. A Box may stand at any one position, but also occupies two positions while transitioning to its new position on its way to its final destination.

Each of the Board's positions has a Spot which records which Box is at that position (or no box) and what transitioning step the Box is currently in. (The Box may be about to arrive, arrived, about to leave, or have left.) Spots are stationary (they are assigned an x-y coordinate on the Board).

main creates a vector of threads, each containing a Board reference and a unique Box id. Each thread is passed the same function, which continually makes requests that the Board move its particular Box to a new position. The Board allows for multiple Spots to be updated at once. The Spot class does not allow two threads to update a Spot concurrently.

Once the threads are created, main's primary thread repeatedly (using a while loop) requests for the Board to broadcast its state (the state of the Boxes and their positions). The information from each broadcast is ultimately received by a Printer and the Printer renders the Board with its Boxes.

Internally the Board pauses all Board changes (Box movements) while it prepares the data for the broadcast. Once the data is collected, it accepts changes while broadcasting out the data. So the received data (received by the Printer) is always a tiny bit stale.

### Moving A Box Updates Spot's SpotType

The transitioning step a box is currently in is named SpotType. The SpotType is saved in the Spot the box is currently at. The Spot contains the Box id and SpotType of the Box that currently occupies its position. It may also be the case that a position is empty. In that case the Spot will have a SpotType::left and a box id of -1. Note a Spot will only change its SpotType in this logical order: SpotType::left, SpotType::to_arrive, SpotType::arrive, SpotType::to_leave, SpotType::left.

Every thread contains one Mover. Every Mover contains one unique box id, and all Movers update Spots according to the correct specified order.

Spot has a unique_lock on its update method, so only one thread can update a Spot at any one time.

Once a thread (with a unique box id) changes a Spot from SpotType::left to SpotType::to_arrive, the Spot is essentially owned by that thread. The Spot contains the thread's unique box id. Other threads trying to enter the Spot with a SpotType of to_arrive will not be allowed to update the Spot. The Spot will return false because the received box id is different from the owning thread's box id.

Other threads must wait for the owning thread to issue the SpotTypes SpotType::arrive through SpotType::left before their requests are successful. It is not until the owning thread issues a request with SpotType::left, that another thread will be able to update that Spot. 

If a Spot containing a particular box id receives a request to update with another box id and a SpotType other than SpotType::to_arrive, then Spot throws an exception, and the program terminates. (Something has gone wrong if a thread is issuing a request other than SpotType::to_arrive at an occupied position. This suggests the thread believes its particular Box is already at that position.) This doesn't happen because of the locking in Spot's methods and Mover's adherence to the correct SpotType order.

### Box's New Positions

The thread function receives a Board reference, a Mover, a Position Manager, and a Decider.

The function contains a loop that only ends when the user closes the window or when the Box reaches its final position.

In the loop, the PositionManager returns its suggested Positions in a vector of Positions with the best Position first. The Decider chooses a position from the vector based on the Positions' SpotTypes. (The Decider gets the SpotTypes from the Board.) Then the Mover requests that the Board move the Box to that chosen position. This involves calling Board's changeSpot() method with the correct SpotTypes in the correct order. (All method calls contain the Mover's boxId, and the first method call contains the SpotType::to_arrive. Once the Board moves the Box to the new position, the loop iterates again asking PositionManager for a vector of possible positions.

It may be that the Mover's first call to changeSpot() returned false. The Board is returning false to notify the caller that the Position is occupied. Although the Decider may have chosen the new position because a call to the Board at that time returned that the Spot was empty. Since the time the Board returned that the position was empty to the time the Mover tried to move the Box, the Spot may have become occupied. It may also have been that the Decider chose a Position it believed would become unoccupied by the time the Mover moved the Box there, but it in fact never became vacant.

At every iteration the PositionManager is asked if the Box is at its end position. If it is, the loop ends and the Box is removed from the Board. The thread function ends.

## License
Across The Plaza was completed in 2024 by Aurea F. Maldonado.

The code that allows rendering of text and blocks on a window is by Amine Ben Hassouna and can be found at https://github.com/aminosbh/sdl2-ttf-sample/blob/master/src/main.c.

I am using the same copyright as Amine Ben Hassouna.

This project is distributed under the terms of the MIT license
[&lt;LICENSE&gt;](LICENSE).

## Build instructions

### Dependencies

```sh
- [Git][]
- C Compiler (gcc, ...)
- [CMake][]
- [SDL2][SDL] library
- [SDL2_ttf][] library
```

### Clone This Repo

In a folder, clone the repository. This will create the PlazaWalkCCode folder.

https://github.com/flocela/PlazaWalkCCode.git

### Install libraries

In order to install the SDL_2 library, in the command line, while in the PlazaWalkCode folder type the following:

```sh
sudo apt-get install libsdl2-ttf-dev
```

The installer will ask if you have additional space and if you would like to continue.

### Make the code

To make the code, create a build folder inside of the PlazaWalkCCode folder. In the PlazaWalkCCode/build folder type:
```sh
cmake .. && make
```

### Run The Project

In the build folder type

```sh
.sdl2-ttf-sample
```

## Run The Tests

```sh
./RunTests
```

