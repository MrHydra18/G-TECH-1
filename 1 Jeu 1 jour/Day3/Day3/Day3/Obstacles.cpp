#include "Obstacles.h"
#include "GameManager.h"

void Obstacles::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRectF(renderer, &m_rect);


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRectF(renderer, &m_rect);
}

void Obstacles::update(float deltaTime)
{
}