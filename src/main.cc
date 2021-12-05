#include "game.hpp"
#include "maze.hpp"
using namespace std;

int main()
{
    //Level level{0.005F, 0.025F, 0.025F, 0, {}, 0.0F, 0.0F, 0.0F, 10, 10, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F};
    //Level level2{0.005F, 0.025F, 0.025F, 0, {}, 0.0F, 0.0F, 0.0F, 15, 15, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 10.0F};
    Level level3{0.0005F, 2, {{4, 0}, {0, 4}}, 0.0004F, 5, 5, {0, 0}, {4, 4}, 5.0F, 2};
    Level level4{0.0005F, 2, {{14, 0}, {0, 14}}, 0.0004F, 15, 15, {0, 0}, {14, 14}, 5.0F, 10};
    Level level5{0.0005F, 2, {{24, 0}, {0, 24}}, 0.0004F, 25, 25, {0, 0}, {24, 24}, 5.0F, 20};
    //Level level2{0.01F, 0.025F, 0.025F, 1, {{0.5F, 0.5F}}, 0.005F, 0.025F, 0.025F , 5, 5, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F};
    //Level level3{0.001F, 0.025F, 1, {{0.6625F, 0.6625F}}, 0.001F, 5, 5, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 225.0F, 2};

    /*Level level1{0.01F, 0.025F, 0.025F, 1, {{0.52F, 0.52F}}, 0.005F, 0.025F, 0.025F , 5, 5, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F};

    Level levela{0.01F, 0.025F, 0.025F, 1, {{0.54F, 0.54F}}, 0.005F, 0.025F, 0.025F , 5, 5, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F};

    Level levelb{0.01F, 0.025F, 0.025F, 1, {{0.56F, 0.56F}}, 0.005F, 0.025F, 0.025F , 5, 5, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F};

    Level levelc{0.01F, 0.025F, 0.025F, 1, {{0.58F, 0.58F}}, 0.005F, 0.025F, 0.025F , 5, 5, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F};

    Level leveld{0.01F, 0.025F, 0.025F, 1, {{0.6F, 0.6F}}, 0.005F, 0.025F, 0.025F , 5, 5, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F};

    Level levele{0.01F, 0.025F, 0.025F, 1, {{0.62F, 0.62F}}, 0.005F, 0.025F, 0.025F , 5, 5, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F};

    Level levelf{0.01F, 0.025F, 0.025F, 1, {{0.64F, 0.64F}}, 0.005F, 0.025F, 0.025F , 5, 5, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F};*/
    Game game;
    game.AddLevel(level3);
    game.AddLevel(level4);
    game.AddLevel(level5);
    /*game.AddLevel(level2);
    game.AddLevel(level3);
    game.AddLevel(level1);
    game.AddLevel(levela);
    game.AddLevel(levelb);
    game.AddLevel(levelc);
    game.AddLevel(leveld);
    game.AddLevel(levele);
    game.AddLevel(levelf);*/
    game.Init();
    game.GenerateNextLevel();
    return 0;
}
