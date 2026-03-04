#pragma once

#include "Menu.h"



class GameOverMenu : public Menu {
private:

	std::vector<std::string> buttonsTexte = { "MAINMENU", "QUIT" };
	std::vector<SDL_Texture*> buttonsTexture;

	size_t selected = 0;

	std::vector<SDL_Rect> buttonsRect;

	int lastMouseX = -1;
	int lastMouseY = -1;

	SDL_Texture* titleBannerTexture = nullptr;

public:

	GameOverMenu(SDL_Renderer* rend, Game* g);

	bool handleInput() override;

	void render() override;

private:
	void executeOption();

};