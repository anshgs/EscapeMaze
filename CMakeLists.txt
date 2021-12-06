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


add_subdirectory(src)
add_subdirectory(tests)

