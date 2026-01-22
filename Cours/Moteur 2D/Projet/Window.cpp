#include "Window.h"
#include<iostream>
#include<SDL.h>

#define W_width 960
#define W_height 480
#define Window_Pos_X 5
#define Window_Pos_Y 25

int Window::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL8init error : " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("TEST moteur2D", Window_Pos_X, Window_Pos_Y, W_width, W_height, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cout << "SDL_CreateWIndow Error : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
}