#pragma once
#include<SDL.h>
#include "Entity.h"
#include<vector>

class GameManager
{
private:

	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning = true;
	std::vector<Entity*> entities;

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
};

