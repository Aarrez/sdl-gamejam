#include "Game.h"
#include <iostream>
#include "SDL3/SDL.h"

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

    eatRect.h = 50;
    eatRect.w = 50;
    eatRect.x = (windowWidth/2) - (eatRect.h/2);
    eatRect.y = (windowHeight/2) - (eatRect.w/2);
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

bool Game::Inputs()
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
                break;
                //Movement input
            case SDLK_w:
                yMovePos = -1;
                break;
            case SDLK_s:
                yMovePos = 1;
                break;
            case SDLK_a:
                xMovePos = -1;
                break;
            case SDLK_d:
                xMovePos = 1;
                break;
            default:;
            }

        }
        else if(e.type == SDL_EVENT_KEY_UP)
        {
            switch (e.key.keysym.sym)
            {
                //Reset movenet input
            case SDLK_w:
                yMovePos = 0;
            case SDLK_s:
                yMovePos = 0;
                break;

            case SDLK_a:
                xMovePos = 0;
            case SDLK_d:
                xMovePos = 0;
                break;
            default:;
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

    if(!rectEaten)
        SDL_RenderFillRect(renderer, &eatRect);

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
    frect.x = std::clamp(frect.x, 0.0f, static_cast<float>(windowWidth));
    frect.y = std::clamp(frect.y, 0.0f, static_cast<float>(windowHeight));

    SDL_bool collision = SDL_HasRectIntersectionFloat(&frect, &eatRect);

    if(collision)
    {
        rectEaten = true;
        std::cout << "In range" << std::endl;
    }
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

