#ifndef GAME_H
#define GAME_H



class Game {
public:
    int windowHeight = 600;
    int windowWidth = 800;
    bool isRunning = true;
    void Init();
    void Run();
    void Destroy();
private:

    class SDL_Renderer* renderer;
    class SDL_Window* window;
    void Inputs();
    void Render();
    void Update();

};



#endif //GAME_H
