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
    Maze* m = new Maze(9, 9);
    REQUIRE(m->GetHeight() == 9);
    REQUIRE(m->GetWidth() == 9);
}

TEST_CASE( "Maze::GenerateMaze Test" ) {
    Maze* m = new Maze(9, 9);
    m->GenerateMaze(9,9);
    //check the bounding wall is closed
    for(int i = 0; i < 9; i++) {
        Locinfo l = m->GetLocinfo(0,i);
        REQUIRE(!l.up);
        l = m->GetLocinfo(i,0);
        REQUIRE(!l.left);
    }
    for(int i = 0; i < 9; i++) {
        Locinfo l = m->GetLocinfo(8,i);
        REQUIRE(!l.down);
        l = m->GetLocinfo(i,8);
        REQUIRE(!l.right);
    }
}

TEST_CASE( "Maze::GetWallCoor Test h = 10"){
    int count = 0;
    //vertical
    for(float i = 0.69f; i >-0.7f; i -= 0.14f) {
        int countrow = 0;
        //horizontal
        for (float j = - 0.69f; j < 0.7f; j += 0.14f ){
            REQUIRE(CastCoorFloatToGrid(j, i,10).first == countrow);
            REQUIRE(CastCoorFloatToGrid(j, i,10).second == count);
            countrow = countrow + 1;
        }
        count = count + 1;
    }
}

TEST_CASE( "Maze::GetWallCoor Test h = 15"){
    int count = 0;
    //vertical
    for(float i = 0.65f; i >-0.7f; i -= 0.0933f) {
        int countrow = 0;
        //horizontal
        for (float j = - 0.65f; j < 0.7f; j += 0.0933f ){
            REQUIRE(CastCoorFloatToGrid(j, i,15).first == countrow);
            REQUIRE(CastCoorFloatToGrid(j, i,15).second == count);
            countrow = countrow + 1;
        }
        count = count + 1;
    }
}

TEST_CASE( "Background color of the maze changes" ) {
  
}

/////////////////////////////Test cases for the utils///////////////////////
TEST_CASE("CastCoorFloatToGrid test") {
    
}

TEST_CASE("CastCoorGridToFloat test") {

}

TEST_CASE("CastToCenter test") {

}

TEST_CASE("GetHitbox test") {

}

TEST_CASE("CollideOnMove test") {

}

TEST_CASE("CollideWalls test") {

}
/////////////////////////////Test cases for the items///////////////////////

TEST_CASE("Set random attributes") {
 

}


/////////////////////////////Test cases for the players//////////////////////
TEST_CASE("Checks the Player object") {
    Player* p1 = new Player(); //Default constructor for this test case

    REQUIRE(p1->GetSizeX() == 0); //checks if the x is 0 for the default constructor
    REQUIRE(p1->GetSizeY() == 0); //checks if the y is 0 for the default constructor
    REQUIRE(p1->GetSpeed() == 0); //checks if the default speed is 0 for the default constructor
    
    float coord_x = 2;
    float coord_y = 2;
    float speed = 5;
    float size = 4;

    p1->SetAttributes({coord_x, coord_y}, speed, size);

    REQUIRE(p1->GetSizeX() == 4);
    REQUIRE(p1->GetSizeY() == 4);
    REQUIRE(p1->GetSpeed() == 5);

    p1->SetSpeed(7);
    REQUIRE(p1->GetSpeed() == 7);

    p1->SetXCoord(3);
    REQUIRE(p1->GetCenter().first == 3);

    p1->SetYCoord(6);
    REQUIRE(p1->GetCenter().second == 6);

    float refresh_rate_ = 2;

    p1->UpdateSpeed(refresh_rate_);
    
    coord_x = 3;
    coord_y = 3;
    speed = 8;
    size = 5;
    p1->SetAttributes({coord_x, coord_y}, speed, size);

    p1->MoveUp();
    REQUIRE(p1->GetCenter().second == 11);

    p1->MoveDown();
    REQUIRE(p1->GetCenter().second == 3);

    p1->MoveLeft();
    REQUIRE(p1->GetCenter().first == -5);

    p1->MoveRight();
    REQUIRE(p1->GetCenter().first == 3);
}



/////////////////////////////Test cases for the players//////////////////////
TEST_CASE("Checks the Player Default Constructor") {
    Player* p1 = new Player(); //Default constructor for this test case

    REQUIRE(p1->GetSizeX() == 0); //checks if the x is 0 for the default constructor
    REQUIRE(p1->GetSizeY() == 0); //checks if the y is 0 for the default constructor
    REQUIRE(p1->GetSpeed() == 0); //checks if the default speed is 0 for the default constructor

}

TEST_CASE("Checks the parameters feeded into the player object") {
    Player* pa = new Player();
    float coord_x = 2;
    float coord_y = 2;
    std::pair<float,float> coords(coord_x,coord_y);
    float speed = 5;
    float size = 4;

    pa->SetAttributes(coords, speed, size);

    REQUIRE(pa->GetSizeX() == 4);
    REQUIRE(pa->GetSizeY() == 4);
    REQUIRE(pa->GetSpeed() == 5);

    pa->SetSpeed(7);
    REQUIRE(pa->GetSpeed() == 7);

}

TEST_CASE("Checks the ai speed") {
    Ai* a1 = new Ai(); //Default constructor for this test case
    float coord_x = 3;
    float coord_y = 3;
    std::pair<float,float> coords(coord_x,coord_y);
    float speed = 8;
    float size = 5;
    
    a1->SetAttributes(coords, speed, size);
    float refresh_rate_ = 2;
    a1->UpdateSpeed(refresh_rate_);
    REQUIRE(a1->GetSpeed() == 0);
    
}

TEST_CASE("Move up") {
    Ai* a2 = new Ai();
    float coord_x = 3;
    float coord_y = 3;
    std::pair<float,float> coords(coord_x,coord_y);
    float speed = 8;
    float size = 5;
    
    a2->SetAttributes(coords, speed, size);
    a2->MoveUp();
    REQUIRE(a2->Getcoordy() == 11);
}

TEST_CASE("Move down") {
    Ai* a3 = new Ai();
    float coord_x = 5;
    float coord_y = 5;
    std::pair<float,float> coords(coord_x,coord_y);
    float speed = 15;
    float size = 10;
    
    a3->SetAttributes(coords, speed, size);
    a3->MoveDown();
    REQUIRE(a3->Getcoordy() == -10);
}

TEST_CASE("Move left") {
    Ai* a4 = new Ai();
    float coord_x = 6;
    float coord_y = 7;
    std::pair<float,float> coords(coord_x,coord_y);
    float speed = 12;
    float size = 9;
    
    a4->SetAttributes(coords, speed, size);
    a4->MoveLeft();
    REQUIRE(a4->Getcoordx() == -6);

}

TEST_CASE("Move right") {
    Ai* a5 = new Ai();
    float coord_x = 5;
    float coord_y = 4;
    std::pair<float,float> coords(coord_x,coord_y);
    float speed = 17;
    float size = 12;
    
    a5->SetAttributes(coords, speed, size);
    a5->MoveRight();
    REQUIRE(a5->Getcoordx() == 22);

}



