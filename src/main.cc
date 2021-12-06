#include "game.hpp"
#include "maze.hpp"

int main()
{

    vector<pair<int, int>> ai_loc_4;
    for(int i = 0; i < 18; i++){
        ai_loc_4.push_back({i,18 - i});
    }

    vector<pair<int, int>> ai_loc_5;
    for(int i = 20; i < 25; i++){
        for(int j = 20; j < 25; j++){
            ai_loc_5.push_back({i,j});
        }
    }
    //Player speed, num_ai, ai_coords, ai_speed, maze width, maze height, player start coords, win tile coords, regen time, num_items
    Level level1{0.001F, 1, {{4, 4}}, 0.0005F, 6, 6, {0,0}, {5, 5}, 5.0F, 3};
    Level level2{0.001F, 3, {{8, 7}, {7, 8}, {8, 8}}, 0.0005F, 10, 10, {0,0}, {5, 5}, 5.0F, 8};
    Level level3{0.0005F, 5, {{12, 12}, {13, 13}, {14, 14}, {12, 13}, {13, 12}}, 0.00001F, 15, 15, {0,0}, {5, 5}, 5.0F, 16};
    Level level4{0.001F, 18, ai_loc_4, 0.0001F, 20, 20, {0,0}, {10, 10}, 1.0F, 20};
    Level level5{0.001F, 25, ai_loc_5, 0.0005F, 25, 25, {0, 0}, {24, 24}, 4.0F, 25};
    
    Game game;
    // game.AddLevel(level1);
    // game.AddLevel(level2);
    // game.AddLevel(level3);
    game.AddLevel(level4);
    game.AddLevel(level5);
    game.Init();
    game.GenerateNextLevel();
    return 0;
}
