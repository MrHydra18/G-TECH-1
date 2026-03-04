#pragma once
#include <vector>
#include <string>
#include <SDL.h>

#include "Menu.h"
#include "LevelManager.h"
#include "AssetsManager.h"
#include "InputManager.h"
#include "UIManager.h"

class SelectionMenu : public Menu {

private:
	std::vector<std::string> levels;

	int selected = 0;
	int posY = 0;
	std::vector<SDL_Rect> buttonRects;

	bool isDraggingScrollbar = false;

	SDL_Texture* scrollbarBg = nullptr;
	SDL_Texture* scrollbarProgress = nullptr;
	SDL_Texture* scrollbarProgressHover = nullptr;
	SDL_Texture* scrollbarThumb = nullptr;
	SDL_Texture* scrollbarThumbHover = nullptr;

	SDL_Texture* titleTexture = nullptr;
	SDL_Texture* buttonTexture = nullptr;

	//% de la taille de la fenetre
	float sbXPercent = 0.9f;
	float sbYPercent = 0.15f;
	float sbWPercent = 0.03f;
	float sbHPercent = 0.75f;
	float tbHPercent = 0.05f;
	float startYPercent = 0.26667f;
	float spacingPercent = 0.13333f;

	int getThumbPosition() const;

public:
	SelectionMenu(SDL_Renderer* rend, Game* g);

	void onEnter() override;

	bool handleInput() override;

	void render() override;
};
