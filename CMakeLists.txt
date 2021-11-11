cmake_minimum_required(VERSION 3.10)

project(EscapeMaze)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(external)
include_directories(includes/)

add_executable(${PROJECT_NAME} src/main.cc src/ai.cc src/functions.cc src/game.cc src/item.cc src/user.cc src/maze.cc)
target_link_libraries(${PROJECT_NAME} glad glfw ${GLFW_LIBRARIES})