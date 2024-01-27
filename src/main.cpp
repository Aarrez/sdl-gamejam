#include "Game/Game.h"

int main()
{
    Game game;

    game.Init();
    game.SetupGame();
    game.Run();
    game.Destroy();
    return 0;
}


