#ifndef LOCINFO_HPP
#define LOCINFO_HPP

// locinfo struct to store the information of each location in the maze
struct Locinfo{
    //true: no wall, false: block
    bool left; //position status of left
    bool right; //position status of right
    bool up; //position status of up
    bool down; //position status of down
    // use in map generation for reducing time complexity of vector search
    bool visited; //determined whether visited or not
    // todo: add constructor;
};

#endif