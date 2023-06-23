# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

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

## Additional Functionality

1. Added a Cmdline user guide to display on ternimal while playing.
2. Added two new commands: (Condition varibale & Mutex):
	i. 'a' key: For pausing game. (If user want to pause game in middle).
	ii.'q' key: For resuming game from pause state.
3. Added controller handler (handleInput()) logic in thread (Pthread).
4. Make Generic Gmae class (Pure Virutal Function) and make SnakeGame as achild of Game class (inheritance).
5. Applied Rule of Three in Snake class.
6. Define renderer object as a unique pointer so throughout the game developer use same renderer object to render game and update the screen.
7. Define SnakeCell() function with template so user can call it to compare any datatype values.

## Rubric Points Addressed

1. functions and control structures:
      1. main.cpp: lines 24
      2. game.cpp: lines 15, 35, 103
      3. renderer.cpp: lines 67
	  4. Snake.cpp: lines 115, 120, 157
2. read/write data from/to file:
      1. game.cpp: lines 22, 117
3. User input/output:
      1. Controller: line 46, 50 (through SDL input)
4. Access specifiers for class members:
      1. game.h: lines 25, 35
	  2. Snake.h: lines 10, 54
5. Object Oriented Programming techniques:
      1. game.cpp: line 59, 70
      2. game.h: lines 24
6. Pass by reference:
	  1. Game.cpp: line 46
7. Rule of Five:
	  1. Snake.h: line 18, 19, 20, 21, 22
	  2. Snake.cpp: line 5, 23, 41, 70, 98
8. Smart pointer:
	  1. main.cpp: lines 18
7. Thread:
	  1. Game.cpp: lines 46
8. mutex:
	  1. Game.cpp: lines: 12, 52, 59, 61
	  2. Controller.cpp: lines 9, 56, 59, 63, 66, 70, 73, 77, 80
9. Condition_variable:
	  1. Game.cpp: lines: 13, 51, 52
	  2. Controler.cpp: lines 10, 52
