#ifndef GAME_H
#define GAME_H
#include <cmath>
#include <SDL_rect.h>
#include <vector>
#include "../Boids/Boid.h"
#include "../Boids/BoidManager.h"

struct Circle
{
    int32_t x, y;
    int32_t r;
};

inline double distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

inline bool check_collison(Circle &A, Circle &B)
{
    if( distance( A.x, A.y, B.x, B.y ) < ( A.r + B.r ) )
    {
        //The circles have collided
        return true;
    }

    //If not
    return false;
}

inline bool check_collision( Circle &A, std::vector<SDL_FRect> &B)
{
    //Closest point on collision box
    int cX, cY;

    //Go through the B boxes
    for( int Bbox = 0; Bbox < B.size(); Bbox++ )
    {
        //Find closest x offset
       if( A.x < B[ Bbox ].x )
        {
            cX = B[ Bbox ].x;
        }
        else if( A.x > B[ Bbox ].x + B[ Bbox ].w )
        {
            cX = B[ Bbox ].x + B[ Bbox ].w;
        }
        else
        {
            cX = A.x;
        }
        //Find closest y offset
        if( A.y < B[ Bbox ].y )
        {
            cY = B[ Bbox ].y;
        }
        else if( A.y > B[ Bbox ].y + B[ Bbox ].h )
        {
            cY = B[ Bbox ].y + B[ Bbox ].h;
        }
        else
        {
            cY = A.y;
        }
        //If the closest point is inside the circle
        if( distance( A.x, A.y, cX, cY ) < A.r )
        {
            //This box and the circle have collided
            return true;
        }
    }

    //If the shapes have not collided
    return false;
}

class Game {
public:
    Game();
    ~Game();
    int windowHeight = 600;
    int windowWidth = 800;
    bool isRunning = true;
    bool isRender = true;
    Circle circle;
    void SetupGame();
    void Run();
private:
    class SDL_Renderer* renderer{};
    class SDL_Window* window{};
    class SDL_Surface* windowSurface{};
    class BoidManager boidManager;
    SDL_Surface* img{};
    int xMovePos {0};
    int yMovePos {0};
    SDL_FRect frect;
    SDL_FRect eatRect;
    std::vector<SDL_FRect> frect_vector;
    int centerX;
    int centerY;
    int32_t circleRadius = 50;
    bool disableCircle = false;
    bool rectEaten = false;
    void DrawCircle(SDL_Renderer * renderer, Circle &circle);
    void Inputs();
    void UpdateGraphics();
    void Update();

};
#endif //GAME_H
