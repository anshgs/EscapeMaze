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
bool CollideAi(vector<float> player_coords, vector<vector<float>> ai_coords, float dx, float dy); //x1 x2 y1 y2

float* GetHitbox(pair<float, float> center, float size_x, float size_y);
float* CoorArray(set<vector<float>> coor);
float* CoorArray(vector<float*> coor);
unsigned int* CoorIndex(size_t size);
std::pair<int,int> CastCoorFloatToGrid(float x, float y, int height_);
// from (y,x) in maze vector --->  center of the cell nin Opengl coordinate
std::pair<float,float> CastCoorGridToFloat(int x, int y, int height_);
// cast coordinates from (y,x) in OpenGl to the center of the closet cell. (still Opengl coor)
std::pair<float,float> CastToCenter(float x, float y, int height_);



#endif