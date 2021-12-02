#include "game.hpp"
#include "maze.hpp"
using namespace std;

int main()
{
    Level level{0.001F, 0.025F, 0.025F, 0, 0.0F, 2, 2, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F};
    Level level2{0.001F, 0.025F, 0.025F, 0, 0.0F, 15, 15, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 10.0F};
    Level level3{0.001F, 0.025F, 0.025F, 0, 0.0F, 20, 20, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 5.0F};
    Game *game = new Game();
    game->AddLevel(level);
    game->AddLevel(level2);
    game->AddLevel(level3);
    game->Init();
    game->GenerateNextLevel();
    return 0;
}
