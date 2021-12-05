#ifndef UTILS_HPP
#define UTILS_HPP
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <vector>
#include <set>

using namespace std;

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
bool CollideOnMove(vector<float> obj1_coords, vector<float> obj2_coords, float dx, float dy);
bool CollideWalls(vector<float> player_coords, set<vector<float>> walls_coords, float dx, float dy);
float* GetHitbox(pair<float, float> center, float size_x, float size_y);
std::pair<int,int> CastCoor_Otom(float x, float y, int height_);
// from (y,x) in maze vector --->  center of the cell nin Opengl coordinate
std::pair<float,float> CastCoor_Mtoo(int x, int y, int height_);
// cast coordinates from (y,x) in OpenGl to the center of the closet cell. (still Opengl coor)
std::pair<float,float> CastToCenter(float x, float y, int height_);



#endif