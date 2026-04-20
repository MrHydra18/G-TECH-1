#include "Entity.h"

bool Entity::collision(SDL_Rect other)
{
	return (other.x < m_rect.x + m_rect.w &&
		other.x + other.w > m_rect.x &&
		other.y < m_rect.y + m_rect.h &&
		other.y + other.h > m_rect.y);
}

bool Entity::checkCollision(SDL_Rect a, SDL_Rect b)
{
	return (a.x < b.x + b.w &&
		a.x + a.w > b.x &&
		a.y < b.y + b.h &&
		a.y + a.h > b.y);
}
	