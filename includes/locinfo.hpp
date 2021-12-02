#ifndef LOCINFO_HPP
#define LOCINFO_HPP

// locinfo struct to store the information of each location in the maze
struct Locinfo{
    //true: no wall, false: block
    bool left;
    bool right;
    bool up;
    bool down;
    // use in map generation for reducing time complexity of vector search
    bool visited;
    bool visited_by_ai;
    // todo: add constructor;
};

#endif