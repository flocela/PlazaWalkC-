# Across The Plaza 

https://github.com/flocela/PlazaWalkCCode/assets/4298622/c6445efa-8f78-4b5d-98b1-78eb97eb2487

This project is a basic sample written in C that demonstrates the usage of the
[SDL2][SDL] and [SDL2_ttf][] libraries. It uses [CMake][] as a build system.

##License
Across The Plaza was completed in 2024 by Aurea F. Maldonado.

The code that allows rendering of text and blocks on a window is by Amine Ben Hassouna and can be found at https://github.com/aminosbh/sdl2-ttf-sample/blob/master/src/main.c.

I am using the same copyright as Amine Ben Hassouna.

This project is distributed under the terms of the MIT license
[&lt;LICENSE&gt;](LICENSE).

## Build instructions

### Dependencies

- [Git][]
- C Compiler (gcc, ...)
- [CMake][]
- [SDL2][SDL] library
- [SDL2_ttf][] library
```sh
### Clone this repo

In a folder, clone the repository. This will create the PlazaWalkCCode folder.

https://github.com/flocela/PlazaWalkCCode.git

### Install libraries

In order to install the SDL_2 library, in the command line, while in the PlazaWalkCode folder type the following:

```
sudo apt-get install libsdl2-ttf-dev
```sh

The installer will ask if you have additional space and if you would like to continue.

### Make the code

To make the code, create a build folder inside of the PlazaWalkCCode folder. In the PlazaWalkCCode/build folder type:
```
cmake .. && make
```sh

### Run the project

In the build folder type

```
.sdl2-ttf-sample
```sh

## Run the tests
```
./RunTests
```sh

