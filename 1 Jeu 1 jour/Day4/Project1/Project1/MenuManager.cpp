#include "MenuManager.h"
#include <cstdio>

bool MenuManager::Init(const char* fontPath)
{
    if (TTF_Init() == -1)
    {
        SDL_Log("[MenuManager] TTF_Init failed: %s", TTF_GetError());
        return false;
    }

    m_fontLarge = TTF_OpenFont(fontPath, 80);
    m_fontMedium = TTF_OpenFont(fontPath, 32);
    m_fontSmall = TTF_OpenFont(fontPath, 20);

    if (!m_fontLarge || !m_fontMedium || !m_fontSmall)
    {
        SDL_Log("[MenuManager] TTF_OpenFont failed: %s", TTF_GetError());
        return false;
    }
    return true;
}

void MenuManager::Shutdown()
{
    if (m_fontLarge) { TTF_CloseFont(m_fontLarge);  m_fontLarge = nullptr; }
    if (m_fontMedium) { TTF_CloseFont(m_fontMedium); m_fontMedium = nullptr; }
    if (m_fontSmall) { TTF_CloseFont(m_fontSmall);  m_fontSmall = nullptr; }
    TTF_Quit();
}

void MenuManager::renderText(SDL_Renderer* r, const char* text, TTF_Font* font, SDL_Color color, int x, int y) const
{
    SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text, color);

    if (!surf) return;

    SDL_Texture* tex = SDL_CreateTextureFromSurface(r, surf);
    SDL_Rect dst{ x, y, surf->w, surf->h };

    SDL_FreeSurface(surf);

    if (!tex) return;

    SDL_RenderCopy(r, tex, nullptr, &dst);
    SDL_DestroyTexture(tex);
}

void MenuManager::renderTextCentered(SDL_Renderer* r, const char* text, TTF_Font* font, SDL_Color color, int y) const
{
    int w = 0, h = 0;
    TTF_SizeUTF8(font, text, &w, &h);
    renderText(r, text, font, color, (SCREEN_W - w) / 2, y);
}

void MenuManager::drawButton(SDL_Renderer* r, SDL_Rect rect,
    SDL_Color fill, SDL_Color border,
    const char* label, TTF_Font* font,
    SDL_Color textColor) const
{
    SDL_SetRenderDrawColor(r, fill.r, fill.g, fill.b, fill.a);
    SDL_RenderFillRect(r, &rect);

    SDL_SetRenderDrawColor(r, border.r, border.g, border.b, border.a);
    SDL_RenderDrawRect(r, &rect);
    SDL_Rect inner{ rect.x + 1, rect.y + 1, rect.w - 2, rect.h - 2 };
    SDL_RenderDrawRect(r, &inner);

    int tw = 0, th = 0;
    TTF_SizeUTF8(font, label, &tw, &th);
    int tx = rect.x + (rect.w - tw) / 2;
    int ty = rect.y + (rect.h - th) / 2;
    renderText(r, label, font, textColor, tx, ty);
}

void MenuManager::drawBackground(SDL_Renderer* r, SDL_Color top, SDL_Color bottom) const
{
    for (int y = 0; y < SCREEN_H; ++y)
    {
        float t = (float)y / (float)SCREEN_H;
        Uint8 cr = (Uint8)(top.r + t * (bottom.r - top.r));
        Uint8 cg = (Uint8)(top.g + t * (bottom.g - top.g));
        Uint8 cb = (Uint8)(top.b + t * (bottom.b - top.b));
        SDL_SetRenderDrawColor(r, cr, cg, cb, 255);
        SDL_RenderDrawLine(r, 0, y, SCREEN_W, y);
    }
}

void MenuManager::renderStartMenu(SDL_Renderer* renderer) const
{
    drawBackground(renderer, { 10, 10, 40, 255 }, { 20, 30, 80, 255 });

    const SDL_Color shadow = { 0,  60, 130, 200 };
    const SDL_Color titleCl = { 100, 220, 255, 255 };

    int tw = 0, th = 0;

    TTF_SizeUTF8(m_fontLarge, "FIND A WAY", &tw, &th);

    int tx = (SCREEN_W - tw) / 2;

    renderText(renderer, "FIND A WAY", m_fontLarge, shadow, tx + 4, 104);
    renderText(renderer, "FIND A WAY", m_fontLarge, titleCl, tx, 100);

    drawButton(renderer, m_playButton,{ 30, 140, 80, 255 }, { 100, 255, 160, 255 }, "PLAY", m_fontMedium, { 210, 255, 230, 255 });
    drawButton(renderer, m_quitButton,{ 30, 140, 80, 255 }, { 100, 255, 160, 255 }, "QUIT", m_fontMedium, { 210, 255, 230, 255 });

}


void MenuManager::renderPause(SDL_Renderer* renderer) const
{
    drawBackground(renderer, { 10, 10, 40, 255 }, { 20, 30, 80, 255 });

    const SDL_Color shadow = { 0,  60, 130, 200 };
    const SDL_Color goClr = { 100, 220, 255, 255 };

    int tw = 0, th = 0;

    TTF_SizeUTF8(m_fontLarge, "PAUSE", &tw, &th);

    int tx = (SCREEN_W - tw) / 2;

    renderText(renderer, "PAUSE", m_fontLarge, shadow, tx + 5, 105);
    renderText(renderer, "PAUSE", m_fontLarge, goClr, tx, 100);

    drawButton(renderer, m_playButton, { 30, 140, 80, 255 }, { 100, 255, 160, 255 }, "RESTART", m_fontMedium, { 210, 255, 230, 255 });
    drawButton(renderer, m_quitButton, { 30, 140, 80, 255 }, { 100, 255, 160, 255 }, "MAIN MENU", m_fontMedium, { 210, 255, 230, 255 });
}

void MenuManager::renderGameOver(SDL_Renderer* renderer, float elapsedTime)
{
    drawBackground(renderer, { 40, 5, 5, 255 }, { 80, 10, 10, 255 });

    const SDL_Color shadow = { 90, 0,  0,  200 };
    const SDL_Color goClr = { 255, 70, 70, 255 };

    int tw = 0, th = 0;

    TTF_SizeUTF8(m_fontLarge, "GAME OVER", &tw, &th);

    int tx = (SCREEN_W - tw) / 2;

    renderText(renderer, "GAME OVER", m_fontLarge, shadow, tx + 5, 105);
    renderText(renderer, "GAME OVER", m_fontLarge, goClr, tx, 100);

    int totalSec = (int)elapsedTime;
    int minutes = totalSec / 60;
    int seconds = totalSec % 60;
    int centis = (int)((elapsedTime - totalSec) * 100);

    char timeBuf[64];
    snprintf(timeBuf, sizeof(timeBuf), "Time survived :  %02d : %02d . %02d", minutes, seconds, centis);

    renderTextCentered(renderer, timeBuf, m_fontMedium, { 255, 220, 80, 255 }, 240);

    drawButton(renderer, m_playButton, { 130, 25, 25, 255 }, { 255, 100, 100, 255 }, "PLAY AGAIN", m_fontMedium, { 255, 200, 200, 255 });
}



bool MenuManager::isPlayClicked(int mx, int my) const
{
    return mx >= m_playButton.x && mx <= m_playButton.x + m_playButton.w &&
        my >= m_playButton.y && my <= m_playButton.y + m_playButton.h;
}

bool MenuManager::isReplayClicked(int mx, int my) const
{
    return mx >= m_playButton.x && mx <= m_playButton.x + m_playButton.w &&
        my >= m_playButton.y && my <= m_playButton.y + m_playButton.h;
}

bool MenuManager::isBoutiqueClicked(int mx, int my) const
{
    return mx >= m_boutiqueButton.x && mx <= m_boutiqueButton.x + m_boutiqueButton.w &&
        my >= m_boutiqueButton.y && my <= m_boutiqueButton.y + m_boutiqueButton.h;
}

bool MenuManager::isQuitClicked(int mx, int my) const
{
    return mx >= m_quitButton.x && mx <= m_quitButton.x + m_quitButton.w &&
        my >= m_quitButton.y && my <= m_quitButton.y + m_quitButton.h;
}