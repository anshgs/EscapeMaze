#ifndef AI_HPP
#define AI_HPP

#include "maze.hpp"
#include "utils.hpp"
#include "locinfo.hpp"
#include<utility>
using namespace std;
class Ai{
    private:
        float coord_x_ = 0;
        float coord_y_ = 0;
        float coord_z_ = 0;
        float speed_ = 0;
        float size_x_ = 0;
        float size_y_ = 0;
        float raw_speed_ = 0;
        Maze* maze_;
    
    public:

        Ai();
        void SetAttributes(pair<float, float> coords, float speed, float size_);
        //void ScanMaze(Maze& maze);
        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();
        float GetSpeed();
        float GetSizeX();
        float GetSizeY();
        float* GetHitbox();
        pair<float, float> GetCenter();
        void UpdateSpeed(float refresh_rate_);
        void Seek(pair<float, float> player_coords, int height, Maze& maze);


};






#endif