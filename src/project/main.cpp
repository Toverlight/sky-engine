#include "../core/game.h"

int main()
{
    Game& game = Game::getInstance();
    game.init("My Game", 800, 600);
    game.run();
    return 0;
}