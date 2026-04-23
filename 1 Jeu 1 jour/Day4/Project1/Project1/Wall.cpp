#include "Wall.h"


void Wall::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRectF(renderer, &m_rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 285, 255);
    SDL_RenderDrawRectF(renderer, &m_rect);
}