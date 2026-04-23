#include "Entity.h"

bool Entity::collision(SDL_FRect other)
{
	return (other.x < m_rect.x + m_rect.w &&
		other.x + other.w > m_rect.x &&
		other.y < m_rect.y + m_rect.h &&
		other.y + other.h > m_rect.y);
}