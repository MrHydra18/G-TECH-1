#include "GameManager.h"
#include "InputManager.h"
#include <SDL.h>
#include <iostream>
#include "Player.h"
#include "Obstacles.h"

void GameManager::Init()
{

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return;
	}

	window = SDL_CreateWindow("Game", 100, 100, 1000, 600, SDL_WINDOW_SHOWN);

	if (!window)
	{
		std::cout << "SDL_CREATEWINDOW Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return;
	}

	Player* player = new Player({ 50, 600 }, { 1, 0 }, 250);
	addEntity(player);

	for (int nb = 0; nb < 8; ++nb)
	{
		Obstacles* obstacle = new Obstacles({ 900, 550 }, { -1, 0 }, 250);
		addEntity(obstacle);

		SDL_

	}

}

void GameManager::Update(float deltaTime)
{
	for (auto& entity : entities)
		entity->update(deltaTime);
}

void GameManager::Shutdown()
{
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}

Entity* GameManager::getEntitieByTag(std::string t)
{
	for (auto& entity : entities) {
		if (entity->tag == t)
			return entity;
	}
	return nullptr;
}

void GameManager::addEntity(Entity* entity)
{
	entities.push_back(entity);
}

void GameManager::handleEvents()
{
	InputManager* inputManager = &InputManager::getInstance();

	if (inputManager->update() == false)
		isRunning = false;

	if (inputManager->IsKeyDown(SDLK_ESCAPE))
	{
		isRunning = false;
	}
}

void GameManager::render() {

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);

	for (auto& entity : entities)
		entity->render(renderer);

	SDL_RenderPresent(renderer);
}