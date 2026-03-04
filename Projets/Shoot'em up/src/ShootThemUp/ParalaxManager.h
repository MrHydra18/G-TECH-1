#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include <fstream>
#include "AssetsManager.h"
#include <filesystem>
#include "Vector2D.h"

class Game;

struct Paralax {
	SDL_Texture* texture;
	SDL_Rect rect;
	Vector2D exactPosition = {0, 0}; 
};


class ParalaxManager {

private:

	std::vector<Paralax> paralaxs;
	std::string path;
	Vector2D baseParalaxSpeed = { 80, 0 };  
	Game* game = nullptr;

	ParalaxManager() = default;

public:

	static ParalaxManager& getInstance() {
		static ParalaxManager instance;
		return instance;
	}

	void setGame(Game* g) {
		game = g;
	}

	void setPath(std::string newPath) {
		path = newPath;
	}

	void setSpeed(int speed) {
		baseParalaxSpeed.x = speed;
	}


	void resetParalax();

	void update(float deltaTime);

	void render(SDL_Renderer* renderer);




};
