#include "game.hpp"

using namespace std;

int main()
{
    /////////////////////////NEED TO CHANGE THE SPEED//////////////////////////
    Level level{0.01F, 0.025F, 0.025F, 0, 0.0F, 5, 5, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 10.0F};
    Level level2{0.01F, 0.025F, 0.025F, 0, 0.0F, 10, 10, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 10.0F};
    Game *game = new Game();
    game->AddLevel(level);
    game->AddLevel(level2);
    game->Init();
    game->GenerateNextLevel();
    return 0;
}
