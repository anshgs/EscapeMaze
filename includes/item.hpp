#ifndef ITEM_HPP
#define ITEM_HPP

#include "user.hpp"
#include <string>

class item {

public:
    item();
    item (std::string item_name, double speed_multiplier, bool invincible);
    void Add_energy();

private:
    std::string item_name_;
    double speed_multiplier_;
    bool invincible_;
    
};





#endif