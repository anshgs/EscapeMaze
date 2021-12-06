#ifndef ITEM_HPP
#define ITEM_HPP

#include "player.hpp"
#include <string>
#include <vector>
#include <utility>

using namespace std;
class Item {

private:
    float coord_x_ = 0.0F; //sets the x coordinate to 0 by default
    float coord_y_ = 0.0F; //sets the y coordinate to 0 by default
    float coord_z_ = 0.0F; //sets the z coordinate to 0 by default
    float size_x_ = 0.02F; //sets the x size to 0.02F by default
    float size_y_ = 0.02F; //sets the y size to 0.02F by default
    int mSize = 1; //sets the mSize to 1 by default
    string item_name_; //declares the item name by default
    bool speed_boost_ = false; //the speed boost status is set to false by default
    bool invincible_ = false; //the invincible status is set to false by default
    bool teleport_ = false; //the teleport status is set to false by default
    vector<string> possible_items_ = {"SpeedBoost" , "Invincible", "Teleport"}; //a vector of possible items

public:
    float GetSizeX(); //returns size of x
    float GetSizeY(); //returns size of y
    float* GetHitbox(); //returns the hitbox
    vector<float> GetCorners(); //returns a vector of corners
    void SetRandomAttributes(int h); //sets the random attributes with the parameter being h
    bool GetSpeedBoost(); //returns the speed boost status
    bool GetInvincible(); //returns the invincible status
    bool GetTeleport(); //returns the teleport status
};

#endif