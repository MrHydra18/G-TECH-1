#pragma once
#include<SDL.h>
#include "Entity.h"
#include "MenuManager.h"
#include<vector>


struct Cell {
	bool wallU = true;
	bool wallL = true;
	bool wallD = true;
	bool wallR = true;
	bool visited = false;
};

class GameManager
{
private:

	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning = true;
	std::vector<Entity*> entities;

	MenuManager m_menuManager;
	GameState   m_gameState = GameState::MENU;

	int m_maxObstacles = 15;
	float m_spawnInterval = 2.0f; 
	float m_spawnTimer = 0.0f;
	int m_obstacleCount = 0;
	int m_lastSpeedUp = 0;
	int minutes;
	int seconds;

	float m_elapsedTime = 0.0f;



	static const int MAZE_COLS = 20;  // nb de colonnes
	static const int MAZE_ROWS = 12;   // nb de lignes
	static const int CELL_W = 100;    // 1000 / 10
	static const int CELL_H = 100;    // 600 / 6

	Cell m_maze[MAZE_ROWS][MAZE_COLS];

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
	void GenerateMaze(int x, int y);
	void BuildMazeWalls();
};

