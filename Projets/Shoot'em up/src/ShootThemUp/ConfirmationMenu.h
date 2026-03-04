#include "Menu.h"



class ConfirmationMenu : public Menu {

private:

	std::vector<std::string> buttonsTexte = { "BACK", "QUIT"};
	std::vector<SDL_Texture*> buttonsTexture;
	std::function<void()> onQuit;

	size_t selected = 0;

	std::vector<SDL_Rect> buttonsRect;

	int lastMouseX = -1;
	int lastMouseY = -1;

	SDL_Texture* titleBannerTexture = nullptr;

public:

	ConfirmationMenu(SDL_Renderer* rend, Game* g, std::function<void()> OQ);

	void onEnter() override;

	bool handleInput() override;

	void render() override;

private:
	void executeOption();

};