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
    m_rect.x += direction.x * speed * deltaTime;
    m_rect.y += direction.y * speed * deltaTime;

    if (m_rect.x <= 0 || m_rect.x + m_rect.w >= 1000)
    {
        direction.x *= -1;
    }
    if (m_rect.y <= 0 || m_rect.y + m_rect.h >= 600)
    {
        direction.y *= -1;
    }
}