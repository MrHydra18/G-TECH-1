#include <iostream>
#include "Window.h"
#include "Sprite.h"

void Window::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init error : " << SDL_GetError() << std::endl;
		exit(1);
	}

	window = SDL_CreateWindow("TEST moteur2D", Window_Pos_X, Window_Pos_Y, W_WIDTH, W_HEIGHT, SDL_WINDOW_SHOWN);

	if (!window)
	{
		std::cout << "SDL_CreateWindow Error : " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
	WindowOpen = true;

	m_Renderer = SDL_CreateRenderer(window, -1, 0);
	if (!m_Renderer)
	{
		std::cout << "SDL_CreateRenderer Error : " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(1);
	}
	InputManager* IM = InputManager::GetInstance();
	bool isRunning = true;
}

void Window::CountTime(Uint64 DeltaTime)
{
	int diff = TARGET_ELAPSED - DeltaTime;
	if (diff > 0)
	{
		SDL_Delay(diff);
		DeltaTime = TARGET_ELAPSED;
	}

	TotalElapsed += DeltaTime;
	if (TotalElapsed >= 1000)
	{
		std::cout << "fps : " << FramCount << std::endl;
		TotalElapsed = 0;
		FramCount = 0;
	}
	FramCount++;
}

void Window::DestroyWindow()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(window);
	m_Renderer = nullptr;
	window = nullptr;
	SDL_Quit();
	WindowOpen = false;
}

void Window::WindowManager()
{
	SDL_SetRenderDrawColor(m_Renderer, 25, 96, 48, 255);
	SDL_RenderClear(m_Renderer);
}

void Window::UpdateWindow()
{
	SDL_RenderPresent(m_Renderer);
}

void Window::Draw(Drawable* d)
{
	d->Draw(this);
}
