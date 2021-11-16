#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "config.hpp"
class Player {

private:
    float coord_x;
    float coord_y;
    float coord_z;
    float speed;
    float size_x;
    float size_y;

public:
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    float GetSpeed();
    float* GetHitbox();

};





#endif