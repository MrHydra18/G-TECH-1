#pragma once
#include<SDL.h>
#include "Entity.h"
#include "MenuManager.h"
#include<vector>


class GameManager
{
private:

	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning = true;
	std::vector<Entity*> entities;

	MenuManager m_menuManager;
	GameState   m_gameState = GameState::START_MENU;

	int m_maxObstacles = 15;
	float m_spawnInterval = 2.0f; 
	float m_spawnTimer = 0.0f;
	int m_obstacleCount = 0;
	int m_lastSpeedUp = 0;
	int minutes;
	int seconds;

	float m_elapsedTime = 0.0f;

	void renderDigit(int digit, int x, int y, int w, int h);
	void renderTime(float elapsed, int x, int y);

	void resetGame();

public:

	static GameManager& GetInstance()
	{
		static GameManager instance;
		return instance;
	}


	void Init();
	void Update(float deltaTime);
	void Shutdown();


	bool running() const { return isRunning; }


	Entity* getEntitieByTag(std::string t);
	void handleEvents();
	void render();
	void addEntity(Entity* entity);
	int getRandomInt(int min, int max);
	void SpawnObjects();
};

