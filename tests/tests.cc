// clang-format on

#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "ai.hpp"
#include "config.hpp"
// #include "game.hpp"
#include "item.hpp"
#include "locinfo.hpp"
#include "maze.hpp"
#include "player.hpp"
#include "utils.hpp"


/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////Test cases for the mazes////////////////////////
TEST_CASE( "Maze initialization" ) {
  
}

TEST_CASE( "Position of the walls in the Maze change" ) {
  
}

TEST_CASE( "Background color of the maze changes" ) {
  
}

/////////////////////////////Test cases for the items///////////////////////

TEST_CASE("Set random attributes") {
 

}


/////////////////////////////Test cases for the players//////////////////////
TEST_CASE("Checks the Player object") {
    Player* p1 = new Player(); //Default constructor for this test case

    REQUIRE(p1.GetSizeX() == 0); //checks if the x is 0 for the default constructor
    REQUIRE(p1.GetSizeY() == 0); //checks if the y is 0 for the default constructor
    REQUIRE(p1.GetSpeed() == 0); //checks if the default speed is 0 for the default constructor
    
    float coord_x = 2;
    float coord_y = 2;
    float speed = 5;
    float size_x = 4;
    float size_y = 4;

    p1.SetAttributes(coord_x, coord_y, speed, size_x, size_y);

    REQUIRE(p1.GetSizeX() == 4);
    REQUIRE(p1.GetSizeY() == 4);
    REQUIRE(p1.GetSpeed() == 5);

    p1.SetSpeed(7);
    REQUIRE(p1.GetSpeed() == 7);

    p1.SetXCoord(3);
    REQUIRE(p1.GetXCoord() == 3);

    p1.SetYCoord(6);
    REQUIRE(p1.GetYCoord() == 6);

    float refresh_rate_ = 2;

    p1.UpdateSpeed(refresh_rate_);
    
    REQUIRE(p1.GetSpeed() == 3.5);

    float coord_x = 3;
    float coord_y = 3;
    float speed = 8;
    float size_x = 5;
    float size_y = 5;
    p1.SetAttributes(coord_x, coord_y, speed, size_x, size_y);

    p1.MoveUp();
    REQUIRE(p1.GetYCoord() == 11);

    p1.MoveDown();
    REQUIRE(p1.GetYCoord() == -5);

    p1.MoveLeft();
    REQUIRE(p1.GetXCoord() == -5);

    p1.MoveRight();
    REQUIRE(p1.GetXCoord() == 11);
}




