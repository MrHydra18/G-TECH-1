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
	Entity* player = getEntitieByTag("Player");

	m_spawnTimer += deltaTime;

	if (m_gameState != GameState::PLAYING)
		return;

	int timePassed = (int)(m_elapsedTime / 20.0f);

	if (timePassed > m_lastSpeedUp)
	{
		m_lastSpeedUp = timePassed;
		for (auto& entity : entities)
		{
			if (entity->tag == "Obstacle")
				entity->speed = (int)(entity->speed * 1.1f);
		}
	}

	if (m_obstacleCount < m_maxObstacles && m_spawnTimer >= m_spawnInterval)
	{
		m_spawnTimer -= m_spawnInterval;

		SpawnObjects();
		++m_obstacleCount;

	}

	for (auto& entity : entities)
	{
		if (entity->tag == "Obstacle")
		{
			if (player->collision(entity->m_rect))
			{
				m_gameState = GameState::GAME_OVER;
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
				int countY = std::max(rE.y + rE.h - rO.y, rO.y + rO.h - rE.y);

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

	addEntity(new Player(Vector2D(500.0f, 300.0f), Vector2D(0.0f, 0.0f), 200));
}
void GameManager::SpawnObjects()
{
	Entity* player = getEntitieByTag("Player");

	Vector2D pos = { getRandomInt(50, 950), getRandomInt(50, 550) };
	Vector2D playerPos = { player->getPosition() };

	int dist = playerPos.Distance(pos);

	if (dist < 100)
	{
		SpawnObjects();
		return;
	}

	Obstacles* newObstacle = new Obstacles(pos, { getRandomInt(-1, 1), getRandomInt(-1, 1) }, 250);
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
		if (m_gameState == GameState::PLAYING || m_gameState == GameState::GAME_OVER)
		{
			resetGame();
			m_gameState = GameState::START_MENU;
			inputManager.resetKey(SDLK_ESCAPE);
			return;
		}
		isRunning = false;
		return;
	}

	if (m_gameState == GameState::START_MENU)
	{
		if (inputManager.IsKeyDown(SDLK_RETURN) || inputManager.IsKeyDown(SDLK_SPACE))
		{
			resetGame();
			m_gameState = GameState::PLAYING;
			inputManager.resetKey(SDLK_RETURN);
			inputManager.resetKey(SDLK_SPACE);
			return;
		}
	}
	else if (m_gameState == GameState::GAME_OVER)
	{
		if (inputManager.IsKeyDown(SDLK_r))
		{
			resetGame();
			m_gameState = GameState::PLAYING;
			inputManager.resetKey(SDLK_r);
			return;
		}
	}

	if (inputManager.IsMouseDown(SDL_BUTTON_LEFT))
	{
		Vector2D mp = inputManager.getMousePos();
		int mx = (int)mp.x;
		int my = (int)mp.y;

		if (m_gameState == GameState::START_MENU && m_menuManager.isPlayClicked(mx, my))
		{
			resetGame();
			m_gameState = GameState::PLAYING;
		}
		else if (m_gameState == GameState::GAME_OVER && m_menuManager.isReplayClicked(mx, my))
		{
			resetGame();
			m_gameState = GameState::PLAYING;
		}
	}
}

void GameManager::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	switch (m_gameState)
	{
	case GameState::START_MENU:
		m_menuManager.renderStartMenu(renderer);
		break;

	case GameState::PLAYING:
		for (auto* e : entities)
			e->render(renderer);
		renderTime(m_elapsedTime, 10, 10);
		break;

	case GameState::GAME_OVER:
		m_menuManager.renderGameOver(renderer, m_elapsedTime);
		break;
	}

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

	minutes = (int)elapsed / 60;
	seconds = (int)elapsed % 60;

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