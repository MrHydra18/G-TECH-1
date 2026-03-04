#pragma once
#include "Menu.h"
#include <vector>



class LevelCrationMenu : public Menu {

	SDL_Texture* bannerTexture;
	SDL_Rect bannerRect;
	std::string titleString;
	SDL_Rect titleRect;
	std::string* actualString;

	
	std::vector<SDL_Texture*> enemysIcons;
	std::vector<SDL_Rect> enemysRect;

	std::vector<SDL_Texture*> bosssIcons;
	std::vector<SDL_Rect> bossRect;

	SDL_Rect saveButtonRect;


	// Grille
	int gridRows = 10;
	int gridCols = 64;
	std::vector<int> gridData;
	int selectedEnemy = 0;

	// Sliders
	int scrollX = 0;
	SDL_Rect sliderXRect;
	bool isDraggingSlider = false;

	// Textures pour le slider
	SDL_Texture* scrollbarProgress;
	SDL_Texture* scrollbarThumb;


public:

	LevelCrationMenu(SDL_Renderer* rend, Game* g);
	void onEnter() override;
	bool handleInput() override;
	void render() override;

	void OnKeyDown(SDL_Keycode key);


};


