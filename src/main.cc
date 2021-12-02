#include "game.hpp"
#include "maze.hpp"
using namespace std;

int main()
{
    //Level level{0.005F, 0.025F, 0.025F, 0, {}, 0.0F, 0.0F, 0.0F, 10, 10, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F};
    //Level level2{0.005F, 0.025F, 0.025F, 0, {}, 0.0F, 0.0F, 0.0F, 15, 15, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 10.0F};
    Level level3{0.005F, 0.025F, 0.025F, 2, {{0.6625F, 0.6625F},{-0.6625F, -0.6625F}}, 0.005F, 0.025F, 0.025F , 20, 20, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F};
    Level level2{0.005F, 0.025F, 0.025F, 1, {{0.5F, 0.5F}}, 0.005F, 0.025F, 0.025F , 15, 15, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F};
    Game game;
    //game.AddLevel(level);
    game.AddLevel(level2);
    game.AddLevel(level3);
    game.Init();
    game.GenerateNextLevel();
    return 0;
}
