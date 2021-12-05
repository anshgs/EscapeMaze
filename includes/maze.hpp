#ifndef MAZE_HPP
#define MAZE_HPP
#include <string>
#include <vector>
#include "locinfo.hpp"
#include <set>
#include <utility>
class Maze { 
    public:
        Maze(int width, int height); //constructor for the Maze by the given paramters being the width and the height 
        int GetWidth(); //returns the width of the maze
        int GetHeight(); //returns the height of the maze
        // return the information at location(x,y) of the maze
        Locinfo GetLocinfo(int y, int x);  //returns the location information while the parameters are y and x
        std::string RandomNeighbor(int y, int x); 
        // generate a maze with size of width * height
        void GenerateMaze(int width, int height);
        // draw maze in cout for tesint purpose [TEST]
        void MazeOut();
        // generate the coordinates of a wall; dim: num of bricks * 12(4*3)
        std::set<std::vector<float>> GetWallCoor(); 
        float* WallCoorArray(std::set<std::vector<float>> coor);
        unsigned int* WallCoorIndex(size_t size); //sets the wall coordinates to size
        std::vector<std::pair<int, const void*>> GetSizeData(); //returns the size of the data
        bool CheckWallOverlap(float y, float x); //check if the map overlaps with y and x


    private:
        int width_; //width of the maze
        int height_; //height of the maze
        std::vector<std::vector<Locinfo>> mazedata_; //stores the Locinfo object in 2d array
};

#endif