cmake_minimum_required(VERSION 3.10)

project(EscapeMaze)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(external)
include_directories(includes/)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()

add_executable(${PROJECT_NAME} src/main.cc src/ai.cc src/utils.cc src/game.cc src/item.cc src/player.cc src/maze.cc src/locinfo.cc)
target_link_libraries(${PROJECT_NAME} glad glfw ${GLFW_LIBRARIES})