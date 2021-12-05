#ifndef MAZE_HPP
#define MAZE_HPP
#include <string>
#include <vector>
#include "locinfo.hpp"
#include <set>
#include <utility>
class Maze { 
    public:
        Maze();
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
        // generate the coordinates of a wall; dim: num of bricks * 12(4*3)
        std::set<std::vector<float>> GetWallCoor();
        float* WallCoorArray(std::set<std::vector<float>> coor);
        unsigned int* WallCoorIndex(size_t size);
        std::vector<std::pair<int, const void*>> GetSizeData();
        bool CheckWallOverlap(float y, float x);


    private:
        int width_;
        int height_;
        std::vector<std::vector<Locinfo>> mazedata_;
};





#endif