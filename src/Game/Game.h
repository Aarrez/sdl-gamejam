#ifndef GAME_H
#define GAME_H
#include <SDL_rect.h>


class Game {
public:
    Game();
    ~Game();
    int windowHeight= 600;
    int windowWidth = 800;
    bool isRunning = true;
    bool isRender = true;
    void SetupGame();
    void Run();
private:
    class SDL_Renderer* renderer{};
    class SDL_Window* window{};
    class SDL_Surface* windowSurface{};
    SDL_Surface* img{};
    int xMovePos {0};
    int yMovePos {0};
    SDL_FRect frect;
    SDL_FRect eatRect;
    bool rectEaten = false;
    bool Inputs();
    void UpdateGraphics();
    void Update();

};



#endif //GAME_H
