#ifndef UTILS_HPP
#define UTILS_HPP

using namespace std;

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
bool CollideOnMove(vector<float> obj1_coords, vector<float> obj2_coords, float dx, float dy);
bool CollideWalls(vector<float> player_coords, set<vector<float>> walls_coords, float dx, float dy);
float* GetHitbox(pair<float, float>);



#endif