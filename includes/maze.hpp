#ifndef MAZE_HPP
#define MAZE_HPP
#include <string>
#include <vector>
#include "locinfo.hpp"
#include <set>
#include <utility>
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
        // generate the coordinates of a wall; dim: num of bricks * 12(4*3)
        std::set<std::vector<float>> GetWallCoor();
        float* WallCoorArray(std::set<std::vector<float>> coor);
        unsigned int* WallCoorIndex(size_t size);
        std::vector<std::pair<int, const void*>> GetSizeData();
        // cast coordinates from (y,x) in OpenGl to (y,x) in the maze double vector
        std::pair<int,int> CastCoor_Otom(float x, float y);
        // from (y,x) in maze vector --->  center of the cell nin Opengl coordinate
        std::pair<float,float> CastCoor_Mtoo(int x, int y);
        // cast coordinates from (y,x) in OpenGl to the center of the closet cell. (still Opengl coor)
        std::pair<float,float> CastToCenter(float x, float y);
        // check if (y,x) from openGl is in a wall false: not in a wall  true: in wall
        bool CheckWallOverlap(float y, float x);


    private:
        int width_;
        int height_;
        std::vector<std::vector<Locinfo>> mazedata_;
};





#endif