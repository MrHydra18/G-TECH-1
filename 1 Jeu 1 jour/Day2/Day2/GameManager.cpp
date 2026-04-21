#include "GameManager.h"
#include "InputManager.h"
#include <SDL.h>
#include <iostream>
#include "Player.h"
#include "Obstacles.h"
#include <random>
#include <algorithm>

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

	Player* player = new Player({ 50, 525 }, { 1, 0 }, 250);
	addEntity(player);

}

void GameManager::Update(float deltaTime)
{
	Entity* player = getEntitieByTag("Player");
	Entity* obstacle = getEntitieByTag("Obstacle");

	if (m_obstacleCount < m_maxObstacles)
	{
		m_spawnTimer += deltaTime;
		if (m_spawnTimer >= m_spawnInterval)
		{
			m_spawnTimer -= m_spawnInterval;

			Obstacles* newObstacle = new Obstacles({ getRandomInt(50, 950), getRandomInt(50, 550) },{ getRandomInt(-1, 1), getRandomInt(-1, 1)},250);
			addEntity(newObstacle);
			++m_obstacleCount;
		}
	}

	for (auto& entity : entities)
	{
		if (entity->tag == "Obstacle")
		{
			if (player->collision(entity->m_rect))
			{
				isRunning = false;
				break;
			}
		}
	}

	for (auto& entity : entities)
	{
		for (auto& other : entities)
		{
			if (entity == other) continue;

			if (!entity->collision(other->m_rect)) continue;

			if (entity->tag == "Obstacle")
			{
				SDL_FRect rE = entity->m_rect;
				SDL_FRect rO = other->m_rect;

				int countX = std::max(rE.x + rE.w - rO.x, rO.x + rO.w - rE.x);
				int countY = std::max(rE.y + rE.h - rO.y, rO.y + rO.h - rO.y);

				if (countX > countY)
				{
					entity->direction.x *= -1;
					other->direction.x *= -1;
				}
				else
				{
					entity->direction.y *= -1;
					other->direction.y *= -1;
				}
			}
		}
	}

	for (auto& entity : entities)
		entity->update(deltaTime);

	m_elapsedTime += deltaTime;
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

int GameManager::getRandomInt(int min, int max)
{
	std::random_device dev;
	std::mt19937 mt(dev());
	std::uniform_int_distribution<int> dist(min, max);

	int value;
	do {
		value = dist(mt);
	} while (value == 0);

	return value;
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

	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	SDL_RenderClear(renderer);

	for (auto& entity : entities)
		entity->render(renderer);

	renderTime(m_elapsedTime, 1000 - 115, 10);

	SDL_RenderPresent(renderer);
}

//Le code termine ici c juste la fonction pour le chronomètre

void GameManager::renderDigit(int digit, int x, int y, int w, int h)
{
	//chaque 1 est un trait soit horisontal soit vertical et on divise les chiffres en 7
	const bool segments[10][7] = 
	{
		{1,1,1,1,1,1,0}, // 0
		{0,1,1,0,0,0,0}, // 1
		{1,1,0,1,1,0,1}, // 2
		{1,1,1,1,0,0,1}, // 3
		{0,1,1,0,0,1,1}, // 4
		{1,0,1,1,0,1,1}, // 5
		{1,0,1,1,1,1,1}, // 6
		{1,1,1,0,0,0,0}, // 7
		{1,1,1,1,1,1,1}, // 8
		{1,1,1,1,0,1,1}, // 9
	};

	int t = 3;

	if (segments[digit][0])
	{
		SDL_Rect r = { x + t, y, w - 2 * t, t };
		SDL_RenderFillRect(renderer, &r);
	}

	if (segments[digit][1])
	{
		SDL_Rect r = { x + w - t, y + t, t, h / 2 - t };
		SDL_RenderFillRect(renderer, &r);
	}

	if (segments[digit][2])
	{
		SDL_Rect r = { x + w - t, y + h / 2, t, h / 2 - t };
		SDL_RenderFillRect(renderer, &r);
	}

	if (segments[digit][3])
	{
		SDL_Rect r = { x + t, y + h - t, w - 2 * t, t };
		SDL_RenderFillRect(renderer, &r);
	}

	if (segments[digit][4])
	{
		SDL_Rect r = { x, y + h / 2, t, h / 2 - t };
		SDL_RenderFillRect(renderer, &r);
	}

	if (segments[digit][5])
	{
		SDL_Rect r = { x, y + t, t, h / 2 - t };
		SDL_RenderFillRect(renderer, &r);
	}

	if (segments[digit][6])
	{
		SDL_Rect r = { x + t, y + h / 2 - t / 2, w - 2 * t, t };
		SDL_RenderFillRect(renderer, &r);
	}
}

void GameManager::renderTime(float elapsed, int x, int y)
{
	int digitW = 20;
	int digitH = 34;
	int gap = 5;
	int colonW = 6;

	int minutes = (int)elapsed / 60;
	int seconds = (int)elapsed % 60;

	int m1 = minutes / 10;
	int m2 = minutes % 10;
	int s1 = seconds / 10;
	int s2 = seconds % 10;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


	renderDigit(m1, x, y, digitW, digitH);
	renderDigit(m2, x + digitW + gap, y, digitW, digitH);


	SDL_Rect dot1 = { x + 2 * (digitW + gap) + 1, y + digitH / 3, colonW / 2, colonW / 2 };
	SDL_Rect dot2 = { x + 2 * (digitW + gap) + 1, y + 2 * digitH / 3, colonW / 2, colonW / 2 };
	SDL_RenderFillRect(renderer, &dot1);
	SDL_RenderFillRect(renderer, &dot2);

	renderDigit(s1, x + 2 * (digitW + gap) + colonW, y, digitW, digitH);
	renderDigit(s2, x + 3 * (digitW + gap) + colonW, y, digitW, digitH);
}