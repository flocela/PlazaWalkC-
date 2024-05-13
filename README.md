# Across The Plaza 

https://github.com/flocela/PlazaWalkCCode/assets/4298622/c6445efa-8f78-4b5d-98b1-78eb97eb2487

A simulation of people walking across a plaza. Each person is represented by a colored box. Each box is in its own thread. If the center of one box tries to enter another box's position, then both boxes turn a darker shade. This represents two people bumping into each other.

## Code Explanation

### Overall 

The plaza is represented by the Board class and the people walking across the plaza to their final destinations are represented by Boxes on the Board. The positions on the Board are represented by a 2-D grid of Spots. Spots are stationary (they are assigned an x-y coordinate on the Board). They contain the id of the Box that is at their position (or -1 if there is no Box at their position) and a SpotType representing the state of the Spot. For example SpotType::left represents the there's no Box at this position, and SpotType::arrive represents a Box having arrived at this position.

main creates a vector of threads, each containing a Board reference and a unique Box id.  The functions contained by the threads continually make Board requests to move their corresponding Box to a new position, that is in order for the box to reach its final destination. The Board allows for multiple Spots to be updated at once. The Spot class does not allow two threads to update it at the same time.

Once the threads are created, main's primary thread iteratively requests for the Board to broadcast its state (the state of the Boxes and their positions). The information from each broadcast is ultimately received by a Printer and the Printer renders the Board with its Boxes.

Internally the Board pauses all Board changes (Box movements) while it prepares the data for the broadcast. Once the data is collected, it accepts changes while broadcasting out the data. So the received data (received by the Printer) is always a tiny bit stale.

### Moving a Box Updates Spot's SpotType

A Spot's SpotType only changes in this order: SpotType::left, SpotType::to_arrive, SpotType::arrive, SpotType::to_leave, SpotType::left.

Every thread contains one Mover. Every Mover contains one unique box id, and all Movers update Spots according to the specified order.

Spot has a unique_lock on its update method, so only one thread can update a Spot at any one time.

Once a thread (with a unique box id) changes a Spot from SpotType::left to SpotType::to_arrive, the Spot is essentially owned by that thread. Other threads trying to enter the Spot with a SpotType of to_arrive will not be allowed to update the Spot (because they have a different box id) and false is returned. Other threads must wait for the owning thread to issue SpotTypes SpotType::arrive through SpotType::left before their requests are successful. It is not until the owning thread issues a request with SpotType::left, that another thread will be able to update the Spot. 

If a Spot containing a particular box id receives a request to update with another box id and a SpotType other than SpotType::to_arrive, then Spot throws an exception, and the program will terminate. This doesn't happen because of the locking and mechanisms and Mover's adherence to the Spot's SpotType order.

### Box's New Positions

The thread function receives a Board reference and a Mover, and is also passed in a Position Manager and a Decider.

The function contains a loop that only ends when the user closes the window or when the Box reaches its final position.

In the loop, the PositionManager returns its suggested Positions in a vector of Positions with the best Position first. The Decider chooses a position from the vector based on the SpotType at that Position. The Decider gets the current SpotType from the Board. Say the position's SpotType is SpotType::left, then the Decider may choose that Position. Then the Mover requests that the Board move the Box to that position. It issues a request containing its box id and SpotType::to_arrive. If the request is successful (Board returns true), then the loop begins again asking PositionManager for a vector of possible positions. Board may return false because the SpotType may have changed from the time Decider approved the move to the time Mover issued the request.

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

