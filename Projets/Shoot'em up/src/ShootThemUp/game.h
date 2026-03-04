#pragma once
#include "InputManager.h"
#include "UIManager.h"
#include "ParalaxManager.h"
#include"Item.h"
#include "Entity.h"
#include"Vaisseau.h"
#include "gameState.h"
#include <vector>
#include <random>	


struct LevelData;


class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;
	Uint32 lastTime;

	std::vector<Entity*> entities;
	std::vector<Entity*> entitiesToAdd;
	InputManager* inputManager;
	LevelData* currentLevel;
	ParalaxManager* paralaxManager;
	Uint32 timebetweenWaves;
	Uint32 lastSpawn;
	int actualWave;
	float scaleRatioX = 1.0f;
	float scaleRatioY = 1.0f;
	int originalWidth;
	int playerMoney = 0;

	int originalHeight;

	float spawnCooldown = 0;
	bool bossFight = false;
	float secondesinceLevelStart = 0.f;


	//player Data


	Game(int width, int height);

	int playerMaxHeath = 5;
	float playerSpeed = 500.f;
	float playerBulletCooldown = 100.f;
	float playerDamageMultiplicator = 1.f;

	friend class ShopMenu;

public:
	int windowWidth;
	int windowHeight;
	~Game();
	GameState currentState = GameState::MainMenu;




	static Game* getInstance() {
		static Game instance(1200, 700);
		return &instance;
	}
	
	void setLevel(LevelData* newLevel);
	void resetLevel();

	bool init(std::string name, int x, int y, bool fullScreen);
	bool init_sound();
	void handleEvents();
	void update(float deltaTime);
	void render();
	void clean();
	void cleanupMarkedEntities();
	int getRandomInt(int min, int max);

	void UpdateSpawnEntity(float dt);
	void dropItemFromEnemy(Enemy* enemy);

	Entity* getEntitieByTag(std::string t);
	std::vector<Entity*> getEntitiesByLayer(std::string l);
	void addEntity(Entity* entity);
	void setState(GameState newState) { currentState = newState; }
	void clearEntity() { entities.clear(); }


	int getPlayerMoney() const { return playerMoney; }
	void setPlayerMoney(int money) { playerMoney = money; }
	void addPlayerMoney(int amount) { playerMoney += amount; }
	void setPLayerMultiplicator(float mult);


	bool running()const { return isRunning; }
	float getDeltaTime();
	void quit();

};
