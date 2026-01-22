#pragma once
#include "Menu.h"
#include "UIManager.h"


class CreditsMenu : public Menu
{
private:
    std::vector<std::string> titles = { "Dev :", "Dev :", "Prof:"};
    std::vector<std::string> texts = { "Iker Cot vaquero", "Eliott Baudoin", "Peter VYSTAVEL"};
    SDL_Texture* tex;
    SDL_Texture* quitTex = nullptr;
    SDL_Rect soundToggleRect;
        



public:

    CreditsMenu(SDL_Renderer* rend, Game* g);
    void onEnter() override;
    bool handleInput() override;
    void render() override;
};