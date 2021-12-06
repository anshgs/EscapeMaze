add_executable(${PROJECT_NAME} main.cc ai.cc utils.cc game.cc item.cc player.cc maze.cc locinfo.cc)
target_link_libraries(${PROJECT_NAME} glad glfw ${GLFW_LIBRARIES})
