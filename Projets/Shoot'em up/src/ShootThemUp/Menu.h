#pragma once
#include <SDL.h>
#include <string>
#include"game.h"

class Game;

class Menu
{
protected:
    std::string menuName;

    Game* game;
    SDL_Renderer* renderer;
    bool isActive = false;

    bool isMouseInRect(int mouseX, int mouseY, SDL_Rect rect) const {
        return (mouseX > rect.x && mouseX < rect.x + rect.w && mouseY > rect.y && mouseY < rect.y + rect.h);
    }

public:

    Menu(const std::string& name, SDL_Renderer* rend, Game* g) : menuName(name), renderer(rend), game(g) {}
    virtual ~Menu() = default;

    virtual void onEnter() { std::cout << "[Menu] enter on" << menuName << "\n"; }
    virtual void onExit() { std::cout << "[Menu] exit off" << menuName << "\n"; }

    virtual void update(float deltaTime) {}
    virtual void render() = 0;

    const std::string& getName() const { return menuName; }
    bool isMenuActive() const { return isActive; }


    void setActive(bool state) { isActive = state; }

    virtual bool handleInput() = 0;
};