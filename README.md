# EscapeMaze - Future Gadget Lab - CS128 Final Project

Welcome to EscapeMaze by Future Gadget Lab! In our game, you're tasked to escape a series of mazes - with a couple catches: 

* You're being chased by AI's who always follow the optimal path to reach you
* The maze walls will randomly regenerate every few seconds. 
 
Items along the way such as portals, speed boosts, and teleports will help you to evade the AI as you try to reach the exit. Do your best to avoid getting caught and reach the end of the final maze!


Built with C++ and OpenGL


## Instructions to install and run the game/tests:
Make sure to have the latest release of Visual Studio and CMake installed before attempting to run this project

Clone the repo recursively with git clone --recursive https://github.com/cs128-2021c/final-project-futuregadgetlab.git  
mkdir build  
cd build  
cmake ..  

To compile the game:
cmake --build . --target EscapeMaze --config Release

To run the game:
./src/Release/EscapeMaze.exe

To compile the test suite:
cmake --build . --target tests --config Release

To run the test suite:
./tests/Release/tests.exe
