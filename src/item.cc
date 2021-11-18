#include "item.hpp"

item::item() : item_name_("") , speed_multiplier_(0) , invincible_(false) { //set the default energy item name to nothing and set the energy level to 0.
}

item::item(std::string item_name, double speed_multiplier, bool invincible) : item_name_(item_name) , speed_multiplier_(speed_multiplier), invincible_(invincible) { //constructor that sets the item name to the parameter's input name and the energy level to the parameter's energy level

}

void item::Add_energy() { //add energy to the user
    if (item_name_ == "Monster") {  ///Monster Drink
        speed_multiplier_ += 20;
    } else if (item_name_ == "Coffee") {  ///Coffee Drink
        speed_multiplier_ += 10;
    }
    
}

