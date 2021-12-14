# CPPND: Capstone Pong Game Final Project

This project builds a classic pong game using the C++ concepts learned in the course. The game has two sliders left and right and a ball. The sliders can only move up and down while the ball can be move anywhere in the screen. The left slider is controlled by keyboard keys 'w' and 's' while the right slider is controlled by keyboard keys 'up' and 'down'. The ball is initially set to move in the leftright direction i.e. at an angle of 45 degree to the left. If any of the slider manage to hit the ball the corresponding slider will get one point and if any of the slider miss the ball, the game will stop. The score of each slider will represent how many times a slider has hit the ball. The score will also be updated at the window title after every 0.5 seconds. To stop the game at any point close the game window. Once the game is over close the window to get the score of each slider.

Expected behaviour: the game should reflect from the sliders and top and bottom walls on hitting the them. If ball manages to hit left or right wall the ball and therefore the game should stop.

## File and Class Structure

Main.cpp initialize the objects controller, game and renderer and will call class: 'game' memeber function 'run' that will be responble for running the game i.e. it will handle input, update the states and render.
Controller class will handle the input given to the sliders using member function 'handleInput'.
Renderer class will render the objects to the screen using memeber function 'render'.
Slider class will update the sliders position based on the user's input given through the keyboard.
Game class will call member functions of above classes which will be responsible for handling input, update the status and rendering. Game class will also update ball's position and direction with each loop of the game.

<img src="Pong game.png"/>

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

1. Make a build directory in the top level directory: `mkdir build && cd build`
2. Compile: `cmake .. && make`
3. Run it: `./SliderGame`.

## 5 rubric points that are addressed in the project:

Rubric point 1: The project code is clearly organized into functions. 
 * This can be seen applied in game.cpp file at line number: 28, 29, 30 where use of different functions can be seen clearly.

Rubric point 2: The project accepts input from a user as part of the necessary operation of the program.
 * This can be seen applied in controller.cpp file at line number 8 where an event is created that later captures keyboard key press as event and based on the updates the slider direction/position.

Rubric point 3: The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
 * This can be seen applied in all .h files for example in slider.h file at line number 8 where class slider is defined which contains different methods and class attributes to hold the data.

Rubric point 4: All class data members are explicitly specified as public, protected, or private.
 * In slider.h file from line number 8 all class data member are either explicitly specified as public or private.

Rubric point 5: At least two variables are defined as references, or two functions use pass-by-reference in the project code.
 * In game.cpp file at line number 15, objects controller and renderer are passed by reference to member function 'Run'.
 * In conroller.cpp file at line number 6, data member gameIsOn is passed by reference to member function 'handleInput'.
