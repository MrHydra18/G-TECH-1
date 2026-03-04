#include "Item.h"
#include "AssetsManager.h"

Item::Item(Vector2D pos, Vector2D dir, float spd, int w, int h, int heal) : Entity("Item"), exactPosition(pos), direction(dir), speed(spd), healAmount(heal)
{
	m_rect.x = (int)pos.x;
	m_rect.y = (int)pos.y;
	m_rect.w = w;
	m_rect.h = h;

	setLayer("item");
	texture = AssetsManager::getInstance().GetTexture("HealthPoints/hearts.png");
}

void Item::render(SDL_Renderer* renderer)
{
	SDL_Rect sourceRect = { 95, 1, 20, 20 };

	if (texture)
		SDL_RenderCopy(renderer, texture, &sourceRect, &m_rect);
	else
		SDL_RenderDrawRect(renderer, &m_rect);
}

void Item::update(float deltaTime)
{
	exactPosition.x += direction.x * deltaTime * speed;
	exactPosition.y += direction.y * deltaTime * speed;

	m_rect.x = (int)exactPosition.x;
	m_rect.y = (int)exactPosition.y;

	if (m_rect.x + m_rect.w < 0)
		markedForDeletion = true;
}