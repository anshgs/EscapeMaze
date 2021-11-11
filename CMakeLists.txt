cmake_minimum_required(VERSION 3.10)

project(EscapeMaze)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(external)
include_directories(includes/)

add_executable(${PROJECT_NAME} src/main.cc)
target_link_libraries(${PROJECT_NAME} glad glfw ${GLFW_LIBRARIES})