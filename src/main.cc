#include "game.hpp"
#include "maze.hpp"
using namespace std;

int main()
{   
    Maze a = Maze(10,10);
    a.GenerateMaze(10,10);
    std::cout<<a.CastCoor_Mtoo(9,7).first<<std::endl;
    std::cout<<a.CastCoor_Mtoo(9,7).second<<std::endl;
    std::cout<<a.CastCoor_Otom(-0.635F, 0.355F).first<<std::endl;
    std::cout<<a.CastCoor_Otom(-0.635F, 0.355F).second<<std::endl;
    Level level{0.01F, 0.025F, 0.025F, 0, 0.0F, 10, 10, {0.355F, -0.635F}, {0.6625F, -0.6625F}, 10.0F};
    Level level2{0.01F, 0.025F, 0.025F, 0, 0.0F, 10, 10, {-0.6625F, 0.6625F}, {0.6625F, -0.6625F}, 10.0F};
    Game *game = new Game();
    game->AddLevel(level);
    game->AddLevel(level2);
    game->Init();
    game->GenerateNextLevel();
    return 0;
}
