#include "utils.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <set>
#include <iostream>
using namespace std;


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
    return x_collide && y_collide;
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

std::pair<int,int> CastCoor_Otom(float y, float x, int height_){
    float range = 1.4f;
    y = -y + 0.7;
    x = x + 0.7;
    // the height of every brick 
    float b_height = 1.4f/height_;
    // first check horizontal --x
    int mx = std::floor(x/b_height);
    // in the most right wall
    if(mx == height_) {
        mx = mx - 1;
    }
    // vertical --y
    int my = std::floor(y/b_height);
    //in the most bottom wall
    if(my == height_) {
        my = my -1;
    }
    std::pair<int,int> output = std::make_pair(my,mx);
    return output; 
}

std::pair<float,float> CastCoor_Mtoo(int y, int x, int height_) {
    float range = 1.4f;
    // the height of every brick 
    float b_height = 1.4f/height_;
    // the width of every brick
    float b_width = 0.01f;
    // horizontal --x
    float x_center = (b_height + b_width)/2;
    float output_x = x * b_height + x_center - 0.7f;
    // vertical --y
    float y_center = (b_height + b_width)/2;
    float output_y = y * b_height + y_center - 0.7f;
    output_y = (-1) * output_y;
    std::pair<float,float> output = std::make_pair(output_y,output_x);
    return output; 
}

std::pair<float,float> CastToCenter(float y, float x, int height_){
    std::pair<int,int> cell = CastCoor_Otom(y, x, height_);
    return CastCoor_Mtoo(cell.first, cell.second, height_);
}