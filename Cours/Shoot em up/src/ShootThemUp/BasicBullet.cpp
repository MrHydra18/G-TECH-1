#include "BasicBullet.h"

void BasicBullet::render(SDL_Renderer* renderer)
{
	SDL_Rect sourceRect = { 16 , 16, 16, 16 };
	SDL_RenderCopy(renderer, texture, &sourceRect, &m_rect);

}

void BasicBullet::update(float deltaTime)
{



	m_rect.x += direction.x * deltaTime * speed;
	m_rect.y += direction.y * deltaTime * speed;
}
