#ifndef ITEM_HPP
#define ITEM_HPP

#include "player.hpp"
#include <string>

using namespace std;
class item {

public:
    item();
    item (string item_name, double speed_multiplier, bool invincible);
    void Add_energy();

private:
    string item_name_;
    double speed_multiplier_;
    bool invincible_;
    
};





#endif