add_executable(tests tests.cc ../src/ai.cc ../src/utils.cc ../src/item.cc ../src/player.cc ../src/maze.cc)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tests glad glfw ${GLFW_LIBRARIES})
