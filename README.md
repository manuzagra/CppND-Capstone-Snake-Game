# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Rubric
* README [3/3]
  * [X] A README with instructions is included with the project.
  * [X] The README indicates the new features you added to the game.
  * [X] The README includes information about each rubric point addressed.
* Compiling and Testing [1/1]
  * [X] The submission must compile and run without errors on the Udacity project workspace.
* Loops, Functions, I/O [3/2]
  * [X] The project demonstrates an understanding of C++ functions and control structures.
    * Everywhere in the project. There are control, loops, good software design...
  * [X] The project reads data from a file and process the data, or the program writes data to a file.
    * Configuration is read from a file so you do not have to compile it every time you change it.
  * [ ] The project accepts user input and processes the input.
  * [X] The project uses data structures and immutable variables.
    * Constant variables as part of the classes, for example, configuration.h or game_object.h
* Object Oriented Programming [5/3]
  * [X] One or more classes are added to the project with appropriate access specifiers for class members.
    * GameObject, Snake, Food, Configuration.
  * [X] Class constructors utilize member initialization lists.
    * GameObject, Snake, Food, Configuration.
  * [X] Classes abstract implementation details from their interfaces.
    * GameObject, Snake, Food.
  * [X] Overloaded functions allow the same function to operate on different parameters.
    * GameObject constructor.
  * [X] Classes follow an appropriate inheritance hierarchy with virtual and override functions.
    * GameObject, Snake, Food.
  * [ ] Templates generalize functions or classes in the project.
* Memory Management [4/3]
  * [X] The project makes use of references in function declarations.
    * Almost everywhere.
  * [ ] The project uses destructors appropriately.
  * [X] The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
    * std::lock_guard is a RAII and it is used in game.cpp.
  * [X] The project follows the Rule of 5.
    * Renderer class followws it.
  * [ ] The project uses move semantics to move data instead of copying it, where possible.
  * [X] The project uses smart pointers instead of raw pointers.
    * The snake and the food are shared_ptr (see game adn renderer).
* Concurrency [2/2]
  * [X] The project uses multithreading.
    * The update of the title of the windows runs in a different thread (see game).
  * [ ] A promise and future is used in the project.
  * [X] A mutex or lock is used in the project.
    * A mutex protects the use of the renderer in the class Game.
  * [ ] A condition variable is used in the project.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
