#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "Vector2D.h"

class Menu;

class UIManager
{
private:
    UIManager() = default;
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

    std::vector<Menu*> menuStack;
    SDL_Renderer* renderer = nullptr;
    std::vector<SDL_Texture*> numtexture;

public:
    static UIManager& getInstance()
    {
        static UIManager instance;
        return instance;
    }




    void init(SDL_Renderer* rend);

    void cleanup();

    void renderText(const char* text, int x, int y, SDL_Color color, int fontSize = 48);

    void renderTitle(const char* text, int x, int y, SDL_Color color, int fontSize = 72);


    void pushMenu(Menu* menu);

    void popMenu();

    void clearMenu();

    void update(float deltaTime);

    void render();

    void renderHP(int hp, int maxHp, int windowWidth, int windowHeight);

    void renderNum(int num, Vector2D pos, int numSize = 32);

    void renderLastMenu();

    bool handleInput();


    bool hasMenus() const {
        return !menuStack.empty();
    }

    Menu& getCurrentMenu() const {
        return *menuStack.back();
    }

    size_t getMenuCount() const {
        return menuStack.size();
    }
};