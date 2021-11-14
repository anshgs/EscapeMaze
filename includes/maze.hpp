#ifndef MAZE_HPP
#define MAZE_HPP
#include <string>
#include <vector>
#include "locinfo.hpp"
class Maze { 
    public:
        Maze(int width, int height);
        int GetWidth();
        int GetHeight();
        // return the information at location(x,y) of the maze
        Locinfo GetLocinfo(int y, int x);
        std::string RandomNeighbor(int y, int x); 
        // generate a maze with size of width * height
        void GenerateMaze(int width, int height);
        // draw maze in cout for tesint purpose [TEST]
        void MazeOut();



    private:
        int width_;
        int height_;
        std::vector<std::vector<Locinfo>> mazedata_;
};





#endif