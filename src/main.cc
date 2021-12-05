#include "game.hpp"
#include "maze.hpp"
using namespace std;

int main()
{
    Level level{0.0005F, 0.025F, 0.025F, 0, 0.0F, 10, 10, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F, 2};
    Level level2{0.0005F, 0.025F, 0.025F, 0, 0.0F, 15, 15, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 10.0F, 10};
    Level level3{0.0005F, 0.025F, 0.025F, 0, 0.0F, 20, 20, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F, 20};
    Game *game = new Game();
    game->AddLevel(level);
    // game->AddLevel(level2);
    // game->AddLevel(level3);
    game->Init();
    game->GenerateNextLevel();
    return 0;
}
