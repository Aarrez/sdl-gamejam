#ifndef GAME_H
#define GAME_H
#include <SDL_rect.h>
#include "../Boids/Boid.h"
#include "../Boids/BoidManager.h"


class Game {
public:
    Game()= default;
    ~Game()= default;

    int windowHeight= 600;
    int windowWidth = 800;
    bool isRunning = true;
    void Init();
    void SetupGame();
    void Run();
    void Destroy();
private:
    class SDL_Renderer* renderer{};
    class SDL_Window* window{};
    class SDL_Surface* windowSurface{};
    SDL_FRect rect;
    class BoidManager boidManager;
    void Inputs();
    void Render();
    void Update();

};



#endif //GAME_H
