#include "game.hpp"

using namespace std;

int main()
{
    Level level{0.001F, 0.025F, 0.025F, 0, 0.0F, 5, 5, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 10.0F};
    Game *game = new Game();
    game->AddLevel(level);
    game->Init();
    game->GenerateNextLevel();
    return 0;
}
