#pragma once
#include "Menu.h"
#include "UIManager.h"


class ShopMenu : public Menu
{
private:
	std::vector<std::string> upgrades;
	int selected = 0;
	SDL_Texture* texture;
	SDL_Texture* quitText;
	SDL_Texture* speed_tex;
	SDL_Texture* dmg_tex;
	SDL_Texture* delay_tex;
	SDL_Texture* hp_tex;
	static int speedcost;
	static int delaycost;
	static int dmgcost;
	static int hpcost;

public:
	ShopMenu(SDL_Renderer* renderer, Game* game);
	bool handleInput() override;
	void render() override;
};