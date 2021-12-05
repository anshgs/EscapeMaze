#ifndef ITEM_HPP
#define ITEM_HPP

#include "player.hpp"
#include <string>

using namespace std;
class item {

public:
    item(); // default constructor for the item class
    item (string item_name, double speed_multiplier, bool invincible); //secondary constructor for the item class where the item name, speed multiplier and the status of invincibility of the player is set by the input parameters
    void Add_energy(); //adds the energy to the player of the game

private:
    string item_name_; //the name of the item
    double speed_multiplier_; //how much speed of the player can be increased
    bool invincible_; //check the invincibility of the player
    
};





#endif