#ifndef PLAYER_HPP
#define PLAYER_HPP


#include<utility>

using namespace std;
class Player {

private:
    float coord_x_ = 0;
    float coord_y_ = 0;
    float coord_z_ = 0;
    float speed_ = 0;
    float size_x_ = 0;
    float size_y_ = 0;
    float raw_speed_ = 0;
public:
    Player();
    void SetAttributes(pair<float, float> coords, float speed, float size_);
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
    void SetSpeed(float speed);
    void SetXCoord(float coord_x);
    void SetYCoord(float coord_y);

};





#endif