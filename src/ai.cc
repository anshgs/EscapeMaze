#include "ai.hpp"

Ai::Ai(){
    
}

void Ai::SetAttributes(float coord_x, float coord_y, float speed, float size_x, float size_y){
    coord_x_ = coord_x;
    coord_y_ = coord_y;
    speed_ = speed;
    raw_speed_ = speed;
    size_x_ = size_x;
    size_y_ = size_y;
}

void Ai::UpdateSpeed(float refresh_rate_){
    if(refresh_rate_!=0){
        speed_ = 0.000167/refresh_rate_ * raw_speed_;
    }
}

void Ai::MoveUp() {
    coord_y_ += speed_;
}

void Ai::MoveDown() {
    coord_y_ -= speed_;
}
    
void Ai::MoveLeft() {
    coord_x_ -= speed_;
}
    
void Ai::MoveRight() {
    coord_x_ += speed_;
}

float Ai::GetSizeX(){
    return size_x_;
}
float Ai::GetSizeY(){
    return size_y_;
}

float Ai::GetSpeed(){
    return speed_;
}

void Ai::ScanMaze(Maze maze){
    maze_ = maze;
}

pair<float, float> Ai::GetCenterYX(){
    return {coord_y_, coord_x_};
}

void Ai::Seek(pair<float, float> player_coords){
    
}

float * Ai::GetHitbox(){
    float x1 = coord_x_ - size_x_/2.0F;
    float x2 = coord_x_ + size_x_/2.0F;
    float y1 = coord_y_ - size_y_/2.0F;
    float y2 = coord_y_ + size_y_/2.0F;
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