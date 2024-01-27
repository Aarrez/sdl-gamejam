#include "Game.h"
#include <iostream>
#include "SDL3/SDL.h"



void Game::Init()
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

    windowSurface = SDL_GetWindowSurface(window);

    if(!windowSurface)
    {
        std::cerr << "Error getting window surface" << std::endl;
    }



    for (int i = 0; i < SDL_GetNumRenderDrivers()-1; ++i)
    {
        std::cout << SDL_GetRenderDriver(i) << std::endl;
    }
    SDL_Renderer* renderer =
        SDL_CreateRenderer(window,
            NULL,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer,
          0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);


}

void Game::SetupGame()
{


}

void Game::Run()
{
    while (isRunning)
    {
        Inputs();
        Update();
        Render();
    }
}

void Game::Destroy()
{
    SDL_DestroyWindow(window);

    //TODO Fix Exeption
    // SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "SDL quit yes";
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
        else if(e.type == SDL_EVENT_KEY_DOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            default:
                continue;
            }

        }
    }
}

void Game::Render()
{
    SDL_UpdateWindowSurface(window);

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,
           0, 0, 255, SDL_ALPHA_OPAQUE);

    rect.h = 200;
    rect.w = 200;
    rect.x = 200;
    rect.y = 200;

    // SDL_RenderRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_RenderLine(renderer, 0, 0, 500, 500);
    // SDL_RenderFillRect(renderer, &rect);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Game::Update()
{
}

