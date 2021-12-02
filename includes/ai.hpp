#ifndef AI_HPP
#define AI_HPP

#include "maze.hpp"
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
        Maze maze_;
    
    public:

        Ai();
        void SetAttributes(float coord_x, float coord_y, float speed, float size_x, float size_y);
        void ScanMaze(Maze maze);
        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();
        float GetSpeed();
        float GetSizeX();
        float GetSizeY();
        float* GetHitbox();
        pair<float, float> GetCenterYX();
        void UpdateSpeed(float refresh_rate_);
        void Seek(pair<float, float> player_coords);


};






#endif