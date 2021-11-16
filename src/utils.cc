#include "utils.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <set>
using namespace std;

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

bool CollideOnMove(vector<float> obj1_coords, vector<float> obj2_coords, float dx, float dy){ //x1 x2 y1 y2
    obj1_coords[0]+=dx;
    obj1_coords[1]+=dx;
    obj1_coords[2]+=dy;
    obj1_coords[3]+=dy;
    bool x_collide = ((obj1_coords[0] < obj2_coords[0] && obj1_coords[1] > obj2_coords[0]) || (obj1_coords[0] < obj2_coords[1] && obj1_coords[1] > obj2_coords[1]) || (obj1_coords[0] < obj2_coords[0] && obj1_coords[1] > obj2_coords[1]) || (obj1_coords[0] > obj2_coords[0] && obj1_coords[1] < obj2_coords[1]));
    bool y_collide = ((obj1_coords[2] < obj2_coords[2] && obj1_coords[3] > obj2_coords[2]) || (obj1_coords[2] < obj2_coords[3] && obj1_coords[3] > obj2_coords[3]) || (obj1_coords[2] < obj2_coords[2] && obj1_coords[3] > obj2_coords[3]) || (obj1_coords[2] > obj2_coords[2] && obj1_coords[3] < obj2_coords[3]));
    obj1_coords[0]-=dx;
    obj1_coords[1]-=dx;
    obj1_coords[2]-=dy;
    obj1_coords[3]-=dy;
    return x_collide || y_collide;
}

bool CollideWalls(vector<float> player_coords, set<vector<float>> walls_coords, float dx, float dy){ //x1 x2 y1 y2
    for(vector<float> wall_coords : walls_coords){
        if(CollideOnMove(player_coords, wall_coords, dx, dy)){
            return true;
        }
    }
    return false;
}

float* GetHitbox(pair<float, float> center, float size_x, float size_y){
    float coord_x = center.first;
    float coord_y = center.second;
    float x1 = coord_x - size_x/2.0F;
    float x2 = coord_x + size_x/2.0F;
    float y1 = coord_y - size_y/2.0F;
    float y2 = coord_y + size_y/2.0F;
    //TODO: fix this
    float * hitbox = new float[12];
    hitbox[0] = x1;
    hitbox[1] = y1;
    hitbox[2] = 0.0F;
    hitbox[3] = x2;
    hitbox[4] = y1;
    hitbox[5] = 0.0F;
    hitbox[6] = x2;
    hitbox[7] = y2;
    hitbox[8] = 0.0F;
    hitbox[9] = x1;
    hitbox[10] = y2;
    hitbox[11] = 0.0F;
    return hitbox;
}
