#ifndef ITEM_HPP
#define ITEM_HPP

#include "player.hpp"
#include <string>
#include <vector>

using namespace std;
<<<<<<< HEAD
class item {

public:
    item(); // default constructor for the item class
    item (string item_name, double speed_multiplier, bool invincible); //secondary constructor for the item class where the item name, speed multiplier and the status of invincibility of the player is set by the input parameters
    void Add_energy(); //adds the energy to the player of the game

private:
    string item_name_; //the name of the item
    double speed_multiplier_; //how much speed of the player can be increased
    bool invincible_; //check the invincibility of the player
=======
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
    
>>>>>>> 7fe2bd48e2f66c8abbc60fdd859b52fbc0b559bc
    
};




#endif