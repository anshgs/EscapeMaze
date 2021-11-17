#include "item.hpp"

item::item() : item_name_("") , energy_level_(0) { //set the default energy item name to nothing and set the energy level to 0.

}

item::item(std::string item_name, int energy_level) : item_name_(item_name) , energy_level_(energy_level) { //constructor that sets the item name to the parameter's input name and the energy level to the parameter's energy level

}

void item::Add_energy() { //add energy to the user
    if (item_name_ == "Monster") {  ///Monster Drink
        energy_level_ += 20;
    } else if (item_name_ == "Coffee") {  ///Coffee Drink
        energy_level_ += 10;
    }
    
}

