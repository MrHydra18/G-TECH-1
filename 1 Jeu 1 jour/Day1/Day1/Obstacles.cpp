#include "Obstacles.h"


void Obstacles::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRectF(renderer, &m_rect);
}

void Obstacles::update(float deltaTime)
{
	float velX = -1.0f;

	m_rect.x += velX * speed * deltaTime;


	if (m_rect.x + m_rect.w < 0)
		m_rect.x = 1000.0f;
}