#include "UIManager.h"
#include "Menu.h"

void UIManager::init(SDL_Renderer* rend) {
    renderer = rend;
    if (TTF_Init() == -1) {
        std::cerr << "[UIManager] TTF_Init failed: " << TTF_GetError() << "\n";
        return;
    }
    for (int i = 0; i < 10; i++) {
        numtexture.push_back(AssetsManager::getInstance().GetTexture("Buttons/" + std::to_string(i) + ".png"));
    }
}

void UIManager::cleanup()
{
    TTF_Quit();
}

void UIManager::renderText(const char* text, int x, int y, SDL_Color color, int fontSize)
{
    if (!renderer) return;

    TTF_Font* dynamicFont = TTF_OpenFont("../../res/Fonts/Foldit.ttf", fontSize);
    if (!dynamicFont) {
        std::cerr << "[UIManager] Failed to load font at size " << fontSize << ": " << TTF_GetError() << "\n";
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(dynamicFont, text, color);
    if (!surface) {
        TTF_CloseFont(dynamicFont);
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        TTF_CloseFont(dynamicFont);
        return;
    }

    SDL_Rect destRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(dynamicFont);
}

void UIManager::renderTitle(const char* text, int x, int y, SDL_Color color, int fontSize)
{
    if (!renderer) return;

    TTF_Font* dynamicFont = TTF_OpenFont("../../res/Fonts/Foldit.ttf", fontSize);
    if (!dynamicFont) {
        std::cerr << "[UIManager] Failed to load font at size " << fontSize << ": " << TTF_GetError() << "\n";
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(dynamicFont, text, color);
    if (!surface) {
        TTF_CloseFont(dynamicFont);
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        TTF_CloseFont(dynamicFont);
        return;
    }

    SDL_Rect destRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(dynamicFont);
}

void UIManager::pushMenu(Menu* menu)
{
    if (!menuStack.empty())
    {
        menuStack.back()->setActive(false);
    }
    menuStack.push_back(menu);
    menu->onEnter();
}

void UIManager::popMenu()
{
    if (menuStack.empty())
        return;
    menuStack.back()->onExit();
    menuStack.pop_back();

    if (!menuStack.empty())
    {
        menuStack.back()->setActive(true);
    }
}

void UIManager::clearMenu()
{
    while (!menuStack.empty())
    {
        popMenu();
    }
    std::cout << "[UIManager] All menus cleared\n";
}

void UIManager::update(float deltaTime) {
    if (!menuStack.empty())
        menuStack.back()->update(deltaTime);
}

void UIManager::render() {
    if (menuStack.size() < 2)
        return;
    for (int i = 0; i < menuStack.size()-1; i++)
    {
        menuStack[i]->render();
    }
}

void UIManager::renderHP(int hp, int maxHp, int windowWidth, int windowHeight)
{
    float winW = windowWidth;
    float winH = windowWidth;

    float barWidth = winW / 6;
    float barHeight = winH / 30;
    float barX = 50;
    float barY = 20;


    SDL_Texture* texture = AssetsManager::getInstance().GetTexture("HealthPoints/hearts.png");
    SDL_Rect rect = { (int)barX, (int)barY, (int)barWidth, (int)barHeight };

    float heartSize = barHeight * 1.5f;

    SDL_Rect drawRect = { (int)(barX - heartSize ), (int)(barY - (heartSize - barHeight) / 2), (int)heartSize, (int)heartSize
    };
    SDL_Rect sourceRect = { 120, 50, 19, 19 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    float ratio = barWidth / maxHp;
    SDL_Rect redRect = { (int)barX, (int)barY, (int)(hp * ratio), (int)barHeight };

    SDL_RenderFillRect(renderer, &redRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderCopy(renderer, texture, &sourceRect, &drawRect);
}

void UIManager::renderNum(int num, Vector2D pos, int numSize)
{
    std::string snum = std::to_string(num);
    for (size_t i = 0; i < snum.size(); i++) {
        SDL_Rect numRect = { i * (numSize - numSize /3) + pos.x, pos.y, numSize, numSize };
        SDL_RenderCopy(renderer, numtexture[snum[i] - '0'], 0, &numRect);
    }
}

void UIManager::renderLastMenu()    
{
    if (menuStack.empty())
        return;
    menuStack.back()->render();
}

bool UIManager::handleInput()
{
    if (!menuStack.empty())
        return menuStack.back()->handleInput();
    return false;
}

