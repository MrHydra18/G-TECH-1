#include "Menu.h"




class PauseMenu : public Menu {

private:

	std::vector<std::string> buttonsTexte = { "RESUME", "MAINMENU", "QUIT" };
	std::vector<SDL_Texture*> buttonsTexture;

	size_t selected = 0;

	std::vector<SDL_Rect> buttonsRect;

	int lastMouseX = -1;
	int lastMouseY = -1;

	SDL_Texture* titleBannerTexture = nullptr;

public:

	PauseMenu(SDL_Renderer* rend, Game* g);

	void onEnter() override;

	bool handleInput() override;

	void render() override;

private:
	void executeOption();

};
