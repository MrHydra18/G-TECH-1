#include "GameManager.h"
#include "InputManager.h"
#include <SDL.h>
#include <iostream>
#include "Obstacles.h"
#include <random>
#include <algorithm>

void GameManager::Init()
{
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Dodge It", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, 0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!m_menuManager.Init("police.ttf"))
	{
		SDL_Log("[GameManager] Impossible de charger la police TTF !");
	}
}

void GameManager::Update(float deltaTime)
{
	InputManager& inputManager = InputManager::getInstance();

	m_spawnTimer += deltaTime;

	if (m_gameState != GameState::PLAYING)
		return;

	int timePassed = (int)(m_elapsedTime / 20.0f);

	if (m_spawnTimer >= m_spawnInterval && m_obstacleCount < m_maxObstacles)
	{
		m_spawnTimer -= m_spawnInterval;

		SpawnObjects();
		++m_obstacleCount;

	}

	for (Entity* entity : entities)
		entity->m_spawn += deltaTime;

	removedCount = 0;

	entities.erase(std::remove_if(entities.begin(), entities.end(), [this](Entity* entity) // Pas réussit à optimiser :)
		{
			if (entity->m_spawn >= m_maxTimeOnScreen)
			{
				delete entity;
				removedCount++;
				return true;
			}
			return false;
		}),
		entities.end()
	);

	for (int i = 0; i < removedCount; i++)
		SpawnObjects();

	if (inputManager.IsMouseDown(SDL_BUTTON_LEFT))
	{
		Vector2D mp = inputManager.getMousePos();
		SDL_FRect precisionRect = { mp.x - m_precision, mp.y - m_precision,
									m_precision * 2.0f, m_precision * 2.0f };

		int spawnCount = 0;

		auto it = entities.begin();
		while (it != entities.end())
		{
			if ((*it)->collision(precisionRect))
			{
				delete* it;
				it = entities.erase(it);
				spawnCount++;
				points++;
			}
			else { ++it; }
		}

		for (int i = 0; i < spawnCount; i++)
			SpawnObjects();
	}

	m_elapsedTime += deltaTime;
}

void GameManager::Shutdown()
{
	for (auto* e : entities)
		delete e;

	entities.clear();

	m_menuManager.Shutdown();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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

void GameManager::resetGame()
{

	for (auto* e : entities)
		delete e;

	entities.clear();

	m_elapsedTime = 0.0f;
	m_spawnTimer = 0.0f;
	m_obstacleCount = 0;
}

void GameManager::SpawnObjects()
{
	float obstacleSize = 75.0f;

	float minDist = obstacleSize + 10.0f;

	Vector2D pos;
	bool validPos = false;
	int attempts = 0;

	while (!validPos && attempts < 20)
	{
		pos = { getRandomInt(75, 925), getRandomInt(75, 525) };
		validPos = true;

		for (Entity* entity : entities)
		{
			Vector2D ePos = entity->getPosition();
			float dx = pos.x - ePos.x;
			float dy = pos.y - ePos.y;
			float dist = std::sqrt(dx * dx + dy * dy);

			if (dist < minDist)
			{
				validPos = false;
				break;
			}
		}
		attempts++;
	}

	if (!validPos)
		return;

	Obstacles* newObstacle = new Obstacles(pos);
	addEntity(newObstacle);
}

void GameManager::handleEvents()
{
	InputManager& inputManager = InputManager::getInstance();

	if (!inputManager.update())
	{
		isRunning = false;
		return;
	}

	if (inputManager.IsKeyDown(SDLK_ESCAPE))
	{
		if (m_gameState == GameState::PLAYING)
		{
			resetGame();
			m_gameState = GameState::PAUSE;
			inputManager.resetKey(SDLK_ESCAPE);
			return;
		}
		isRunning = false;
		return;
	}

	if (inputManager.IsMouseDown(SDL_BUTTON_LEFT))
	{
		Vector2D mp = inputManager.getMousePos();
		int mx = (int)mp.x;
		int my = (int)mp.y;

		if (m_gameState == GameState::MENU && m_menuManager.isPlayClicked(mx, my))
		{
			resetGame();
			m_gameState = GameState::PLAYING;
		}
		else if (m_gameState == GameState::MENU && m_menuManager.isQuitClicked(mx, my))
		{
			isRunning = false;
		}
		else if (m_gameState == GameState::PAUSE && m_menuManager.isQuitClicked(mx, my))
		{
			m_gameState = GameState::MENU;
		}
		else if (m_gameState == GameState::PAUSE && m_menuManager.isReplayClicked(mx, my))
		{
			resetGame();
			m_gameState = GameState::PLAYING;
		}
		else if (m_gameState == GameState::PAUSE && m_menuManager.isBoutiqueClicked(mx, my))
		{
			m_gameState = GameState::SHOP;
		}
		else if (m_gameState == GameState::SHOP && m_menuManager.isBoutiqueClicked(mx, my))
		{
			if (points >= m_prixDelay)
			{
				m_maxTimeOnScreen *= 1.05f;
				points -= m_prixDelay;
				m_prixDelay *= 1.15f;
			}
		}
		else if (m_gameState == GameState::SHOP && m_menuManager.isReplayClicked(mx, my))
		{
			if (points >= m_prixPrecision)
			{
				m_precision *= 1.05f;
				points -= m_prixPrecision;
				m_prixPrecision *= 1.15f;
			}
		}
		else if (m_gameState == GameState::SHOP && m_menuManager.isQuitClicked(mx, my))
		{
			m_gameState = GameState::PAUSE;
		}
	}
}

void GameManager::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	switch (m_gameState)
	{
	case GameState::MENU:
		m_menuManager.renderStartMenu(renderer);
		break;

	case GameState::PLAYING:
		for (auto* e : entities)
			e->render(renderer);

		renderPoints(points, 850, 10);
		break;

	case GameState::PAUSE:
		m_menuManager.renderPause(renderer);
		renderPoints(points, 850, 10);
		break;

	case GameState::SHOP:
		m_menuManager.renderShop(renderer, m_prixPrecision, m_prixDelay);
		renderPoints(points, 850, 10);
		break;
	}

	SDL_RenderPresent(renderer);
}

//Le code termine ici c juste la fonction pour le chronomètre et les points

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

void GameManager::renderPoints(int pts, int x, int y)
{
	int digitW = 20;
	int digitH = 34;
	int gap = 5;

	int val = pts < 9999 ? pts : 9999;

	int d0 = val / 1000;
	int d1 = (val / 100) % 10;
	int d2 = (val / 10) % 10;
	int d3 = val % 10;

	SDL_SetRenderDrawColor(renderer, 255, 220, 50, 255);

	renderDigit(d0, x, y, digitW, digitH);
	renderDigit(d1, x + (digitW + gap), y, digitW, digitH);
	renderDigit(d2, x + 2 * (digitW + gap), y, digitW, digitH);
	renderDigit(d3, x + 3 * (digitW + gap), y, digitW, digitH);
}
