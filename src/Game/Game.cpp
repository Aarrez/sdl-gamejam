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

    // for (int i = 0; i < SDL_GetNumRenderDrivers()-1; ++i)
    // {
    //     std::cout << SDL_GetRenderDriver(i) << std::endl;
    // }
    renderer =
        SDL_CreateRenderer(window,
            NULL,
            0);
}

void Game::SetupGame()
{
    rect.h = 200;
    rect.w = 200;
    rect.x = (windowWidth/2) - (rect.h/2);
    rect.y = (windowHeight/2) - (rect.w/2);
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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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
    SDL_SetRenderDrawColor(renderer,
           0, 255, 0, 255);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer,
           255, 0, 0, 255);

    SDL_RenderFillRect(renderer, &rect);
    //Paint Window
    SDL_RenderPresent(renderer);
}

void Game::Update()
{
}

