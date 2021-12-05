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
    Player(); //default constructor for player class
    void SetAttributes(float coord_x, float coord_y, float speed, float size_x, float size_y); //sets attributes using the x coordinates, y coordinates, speed, size of x, and size of y
    void MoveUp(); //function to move up
    void MoveDown(); //function to move down
    void MoveLeft(); //function to move left
    void MoveRight(); //function to move right
    float GetSpeed(); //returns the speed of the player
    float GetSizeX(); //returns the size of x
    float GetSizeY(); //returns the size of y
    float* GetHitbox(); //returns the hitbox
    void UpdateSpeed(float refresh_rate_); //updates the speed by using the refresh rate as the parameter
    void SetSpeed(float speed); //set the speed by the given speed parameter
    void SetXCoord(float coord_x); //set the x cord by the given x coord
    void SetYCoord(float coord_y); //set the y cord by the given y coord
};

#endif