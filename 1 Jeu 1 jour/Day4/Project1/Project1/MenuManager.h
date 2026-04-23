#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

enum class GameState
{
    MENU,
    PLAYING,
    PAUSE,
    GAME_OVER
};

class MenuManager
{
private:
    TTF_Font* m_fontLarge = nullptr;  // titres
    TTF_Font* m_fontMedium = nullptr;  // boutons
    TTF_Font* m_fontSmall = nullptr;  // sous-titres

    const int SCREEN_W = 1000;
    const int SCREEN_H = 600;

    SDL_Rect m_playButton{ 375, 355, 250, 65 };
    SDL_Rect m_quitButton{ 375, 450, 250, 65 };
    SDL_Rect m_boutiqueButton{ 375, 355, 250, 65 };

    void renderText(SDL_Renderer* r, const char* text, TTF_Font* font, SDL_Color color, int x, int y) const;

    void renderTextCentered(SDL_Renderer* r, const char* text, TTF_Font* font, SDL_Color color, int y) const;

    void drawButton(SDL_Renderer* r, SDL_Rect rect, SDL_Color fill, SDL_Color border, const char* label, TTF_Font* font, SDL_Color textColor) const;

    void drawBackground(SDL_Renderer* r, SDL_Color top, SDL_Color bottom) const;

public:

    bool Init(const char* fontPath);
    void Shutdown();

    void renderStartMenu(SDL_Renderer* renderer) const;
    void renderPause(SDL_Renderer* renderer) const;
    void renderGameOver(SDL_Renderer* renderer, float elapsedTime);

    bool isPlayClicked(int mx, int my)   const;
    bool isQuitClicked(int mx, int my)   const;
    bool isReplayClicked(int mx, int my) const;
    bool isBoutiqueClicked(int mx, int my) const;
};