#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {

private:
    float coord_x_ = 0;
    float coord_y_ = 0;
    float coord_z_ = 0;
    float speed_ = 0;
    float size_x_ = 0;
    float size_y_ = 0;

public:
    Player();
    void SetAttributes(float coord_x, float coord_y, float speed, float size_x, float size_y);
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    float GetSpeed();
    float GetSizeX();
    float GetSizeY();
    float* GetHitbox();

};





#endif