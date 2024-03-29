#include "Game.h"
#include <iostream>
#include <algorithm>
#include "SDL3/SDL.h"
#include "../Boids/BoidManager.h"
#include "../Boids/Boid.h"


Game::Game()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        std::cerr << "Error initializing SDL" << std::endl;
        return;
    }
    const SDL_DisplayMode* display_mode =
        SDL_GetCurrentDisplayMode(0);

    window = SDL_CreateWindow("Test",
        windowWidth, windowHeight,
        SDL_WINDOW_BORDERLESS);
    if(!window)
    {
        std::cerr << "Error Creating SDL window" << std::endl;
        return;
    }

    // windowSurface = SDL_GetWindowSurface(window);
    //
    // if(!windowSurface)
    // {
    //     std::cerr << "Error getting windowSurface" << std::endl;
    //     return;
    // }
    renderer =
        SDL_CreateRenderer(window,
            NULL,
            0);

    if(!renderer)
    {
        std::cerr << "Error creating Renderer" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return;
    }

    //Uncomment if using windowSurface
    // img = SDL_LoadBMP("img/sample.bmp");
    // if(!img)
    // {
    //     std::cerr << "Error getting BMP";
    //     return;
    // }
}

void Game::SetupGame()
{
    //Rendering rectangle
    frect.h = 100;
    frect.w = 100;
    frect.x = 0;
    frect.y = 0;
    frect_vector.push_back(frect);

    eatRect.h = 50;
    eatRect.w = 50;
    eatRect.x = (windowWidth/2) - (eatRect.h/2);
    eatRect.y = (windowHeight/2) - (eatRect.w/2);

    centerX = windowWidth/2;
    centerY = windowHeight/2;
    circle.x = centerX;
    circle.y = centerY;
    circle.r = circleRadius;

    SDL_Rect boidField;
    boidField.x = 0;
    boidField.y = 0;
    boidField.h = windowHeight;
    boidField.w = windowWidth;
    boidManager.InitBoids(boidField, 100);
}

void Game::Run()
{
    while (isRunning)
    {
        Inputs();
        Update();
        UpdateGraphics();
    }
}

void Game::Inputs()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            isRunning = false;
            break;
        }

        if(e.type == SDL_EVENT_KEY_DOWN)
        {
            switch (e.key.keysym.sym)
            {
                //Close program input
            case SDLK_ESCAPE:
                isRunning = false;
                continue;
                //Movement input
            case SDLK_w:
                yMovePos = -1;
		continue;
            case SDLK_s:
                yMovePos = 1;
		continue;
            case SDLK_a:
                xMovePos = -1;
		continue;
            case SDLK_d:
                xMovePos = 1;
		continue;
            default:
                std::cout << "x: " << frect.x << std::endl;
                std::cout << "y: " << frect.y << std::endl;
            }

        }
        else if(e.type == SDL_EVENT_KEY_UP)
        {
            switch (e.key.keysym.sym)
            {
	      // Reset movement values 
            case SDLK_w:
	      if (yMovePos < 0)
                yMovePos = 0;
	      continue;
            case SDLK_s:
	      if (yMovePos > 0)
                yMovePos = 0;
	      continue;
            case SDLK_a:
	      if (xMovePos < 0)
                xMovePos = 0;
	      continue;
            case SDLK_d:
	      if (xMovePos > 0)
                xMovePos = 0;
	      continue;
            default:
	      continue;
            }
        }
    }
}

void Game::UpdateGraphics()
{
    SDL_SetRenderDrawColor(renderer,
           40, 40, 40, 255);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer,
           255, 255, 255, 255);

    SDL_RenderFillRect(renderer, &frect);

    SDL_SetRenderDrawColor(renderer,
          0, 155, 0, 255);

    if(rectEaten)
        DrawCircle(renderer, circle);

    SDL_SetRenderDrawColor(renderer,
         0, 0, 255, 255);

    if(!rectEaten)
        SDL_RenderFillRect(renderer, &eatRect);

    // Draw the boids
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    for (const Boid& boid : boidManager.boids)
    {
      SDL_RenderFillRect(renderer, &boid.rect);
    }

    //Paint Window
    SDL_RenderPresent(renderer);

    // SDL_BlitSurface(img, NULL,
    //   windowSurface,NULL);
    // SDL_UpdateWindowSurface(window);
}

void Game::Update()
{

    frect.x += xMovePos;
    frect.y += yMovePos;
    float tempw = static_cast<float>(windowWidth) - frect.w;
    float temph = static_cast<float>(windowHeight) - frect.h;
    frect.x = std::clamp(frect.x, 0.0f, tempw);
    frect.y = std::clamp(frect.y, 0.0f, temph);




    if(rectEaten)
    {
        if(circle.r < 100)
            circle.r++;;

        circle.x = frect.x + frect.w/2;
        circle.y = frect.y + frect.h/2;
        if(check_collision(circle, frect_vector))
        {

        }
    }
    if(SDL_HasRectIntersectionFloat(&frect, &eatRect) && rectEaten == false)
    {
        rectEaten = true;
        // std::cout << "In range" << std::endl;
    }



    boidManager.MoveBoids();
}

Game::~Game()
{
    // SDL_DestroySurface(windowSurface);
    // SDL_DestroySurface(img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "SDL quit yes";
}

void Game::DrawCircle(SDL_Renderer * renderer, Circle &circle)
{
    const int32_t diameter = (circle.r * 2);

    int32_t x = (circle.r - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle

        SDL_RenderPoint(renderer, circle.x + x, circle.y - y);
        SDL_RenderPoint(renderer, circle.x + x, circle.y + y);
        SDL_RenderPoint(renderer, circle.x - x, circle.y - y);
        SDL_RenderPoint(renderer, circle.x - x, circle.y + y);
        SDL_RenderPoint(renderer, circle.x + y, circle.y - x);
        SDL_RenderPoint(renderer, circle.x + y, circle.y + x);
        SDL_RenderPoint(renderer, circle.x - y, circle.y - x);
        SDL_RenderPoint(renderer, circle.x - y, circle.y + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}


