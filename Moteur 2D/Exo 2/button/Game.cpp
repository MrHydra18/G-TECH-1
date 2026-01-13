#include "Game.h"
#include <iostream>
#include "HandleEvents.h"
#include "Boutton.h"

void Game::Loop()
{
	SDL_Window* window = SDL_CreateWindow("Button", 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	HandleEvents e;
	Boutton b;

	while (isPlaying)
	{
		e.Events(*this, b);
		b.Draw(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}