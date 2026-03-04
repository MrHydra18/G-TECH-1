#include "Enemy.h"

void Enemy::render(SDL_Renderer* renderer) {
	if (texture) {
		SDL_RenderCopy(renderer, texture, nullptr, &m_rect);
	}
}

void Enemy::update(float deltaTime) {

    exactPosition.x += direction.x * deltaTime * speed;
    exactPosition.y += direction.y * deltaTime * speed;

    m_rect.x = (int)exactPosition.x;
    m_rect.y = (int)exactPosition.y;

}
