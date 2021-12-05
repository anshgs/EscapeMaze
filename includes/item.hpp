#ifndef ITEM_HPP
#define ITEM_HPP

#include "player.hpp"
#include <string>
#include <vector>

using namespace std;
class Item {

private:
    float coord_x_ = 0.0F;
    float coord_y_ = 0.0F;
    float coord_z_ = 0.0F;
    float size_x_ = 0.02F;
    float size_y_ = 0.02F;
    int mSize = 1;
    string item_name_;
    bool speed_boost_ = false;
    bool invincible_ = false;
    bool teleport_ = false;
    vector<string> possible_items_ = {"SpeedBoost" , "Invincible", "Teleport"};

public:
    
    float GetSizeX();
    float GetSizeY();
    float* GetHitbox();
    vector<float> GetCorners();
    void SetRandomAttributes(int h);
    bool GetSpeedBoost();
    bool GetInvincible();
    bool GetTeleport();
    
    
};




#endif