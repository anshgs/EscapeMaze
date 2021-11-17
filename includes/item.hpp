#ifndef ITEM_HPP
#define ITEM_HPP

#include "user.hpp"
#include <string>

class item {

public:
    item();
    item (std::string item_name, int energy_level);
    void Add_energy();

private:
    std::string item_name_;
    int energy_level_;
};





#endif