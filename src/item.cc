#include "item.hpp"
#include "utils.hpp"

void Item::SetRandomAttributes(int h) { //add energy to the user
    int idx = rand()%possible_items_.size(); //random idx number generator from 0 to 2
    item_name_ = possible_items_.at(idx);
    mSize = h;
    coord_x_ = -0.7f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.4f)));
    coord_y_ = -0.7f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.4f)));

    float tx = CastToCenter(coord_x_, coord_y_, mSize).first;
    float ty = CastToCenter(coord_x_, coord_y_, mSize).second;

    coord_x_ = tx;
    coord_y_ = ty;

    if (item_name_ == "SpeedBoost") {  
        speed_boost_ = true;
    } else if (item_name_ == "Teleport"){
        teleport_ = true;
    } else if (item_name_ == "Invincible"){
        invincible_ = true;
    }

    
}

float Item::GetSizeX(){
    return size_x_;
}
float Item::GetSizeY(){
    return size_y_;
}


float * Item::GetHitbox(){
    float x1 = coord_x_ - size_x_/2.0F;
    float x2 = coord_x_ + size_x_/2.0F;
    float y1 = coord_y_ - size_y_/2.0F;
    float y2 = coord_y_ + size_y_/2.0F;
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

vector<float> Item::GetCorners(){
    float x1 = coord_x_ - size_x_/2.0F;
    float x2 = coord_x_ + size_x_/2.0F;
    float y1 = coord_y_ - size_y_/2.0F;
    float y2 = coord_y_ + size_y_/2.0F;
    vector<float> hitbox;
    hitbox.push_back(x1);
    hitbox.push_back(x2);
    hitbox.push_back(y1);
    hitbox.push_back(y2);
    return hitbox;
}

bool Item::GetSpeedBoost() {
    return speed_boost_;
}
    
bool Item::GetInvincible() {
    return invincible_;
}

bool Item::GetTeleport() {
    return teleport_;
}

pair<float, float> Item::GetCenter(){
    return {coord_x_, coord_y_};
}
