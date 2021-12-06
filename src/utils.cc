#include "utils.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <set>
#include<math.h>
#include <iostream>


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

bool CollideAi(vector<float> player_coords, vector<vector<float>> ai_coords, float dx, float dy){ //x1 x2 y1 y2
    for(vector<float> ai_coord : ai_coords){
        if(CollideOnMove(player_coords, ai_coord, dx, dy)){
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

float* CoorArray(set<vector<float>> coor) {
    float *output = new float[coor.size() * 4 * 3];
    set<vector<float>>::iterator wIt = coor.begin();
    int pos = 0;
    while(wIt != coor.end()) {
        vector<float> cur = (*wIt);
        float x1 = cur[0];
        float x2 = cur[1];
        float y1 = cur[2];
        float y2 = cur[3];
        output[pos]=x1;
        output[pos+1]=y1;
        output[pos+2]=0.0f;
        output[pos+3]=x2;
        output[pos+4]=y1;
        output[pos+5]=0.0f;
        output[pos+6]=x2;
        output[pos+7]=y2;
        output[pos+8]=0.0f;
        output[pos+9]=x1;
        output[pos+10]=y2;
        output[pos+11]=0.0f;
        pos+=12;
        wIt++;
    }
    return output;
}

float* CoorArray(vector<float*> coor) {
    float *output = new float[coor.size() * 4 * 3];
    int pos = 0;
    for(float* cur : coor) {
        for(int i = 0; i < 12; i++){
            output[pos+i] = cur[i];
        }
        pos+=12;
    }
    return output;
}

unsigned int* CoorIndex(size_t size){
    unsigned int* output = new unsigned int[size*6];
    int pos = 0;
    for(size_t i = 0; i< size; i++){
        output[pos] = 4*i;
        output[pos+1] = 4*i+1;
        output[pos+2] = 4*i+3;
        output[pos+3] = 4*i+1;
        output[pos+4] = 4*i+2;
        output[pos+5] = 4*i+3;
        pos+=6;
    }
    return output;

}
pair<int,int> CastCoorFloatToGrid(float x, float y, int height_){
    float range = 1.4f;
    y = -y + 0.7;
    x = x + 0.7;
    // the height of every brick 
    float b_height = 1.4f/height_;
    // first check horizontal --x
    int mx = floor(x/b_height);
    // in the most right wall
    if(mx == height_) {
        mx = mx - 1;
    }
    // vertical --y
    int my = floor(y/b_height);
    //in the most bottom wall
    if(my == height_) {
        my = my -1;
    }
    pair<int,int> output = make_pair(mx,my);
    return output; 
}

pair<float,float> CastCoorGridToFloat(int x, int y, int height_) {
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
    pair<float,float> output = make_pair(output_x,output_y);
    return output; 
}

pair<float,float> CastToCenter(float x, float y, int height_){
    pair<int,int> cell = CastCoorFloatToGrid(x, y, height_);
    return CastCoorGridToFloat(cell.first, cell.second, height_);
}