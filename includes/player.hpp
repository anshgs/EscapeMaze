#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player { //class for the player

private:
    float coord_x_ = 0; //default x coordinate is 0
    float coord_y_ = 0; //default y coordinate is 0
    float coord_z_ = 0; //default z coordinate is 0
    float speed_ = 0; //default speed is 0
    float size_x_ = 0; //default x size is 0
    float size_y_ = 0; //default y size is 0
    float raw_speed_ = 0; //default raw speed is 0
public:
    Player(); //default constructor for the player
    void SetAttributes(float coord_x, float coord_y, float speed, float size_x, float size_y); //sets the attributes of the player using x coord_x, y coord_y, speed, size of x and size of y as input parameters
    void MoveUp(); //moves the player up
    void MoveDown(); //moves the player down
    void MoveLeft(); //moves the player left
    void MoveRight(); //moves the player right
    float GetSpeed(); //returns the speed
    float GetSizeX(); //returns the size of x
    float GetSizeY(); //returns the size of y
    float* GetHitbox(); //gets the hit box
    void UpdateSpeed(float refresh_rate_); //updates the speed by using the parameter refresh rate

};





#endif