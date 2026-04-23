#pragma once
#include "Entity.h"

class Wall : public Entity
{

public:

	Wall(SDL_FRect pos) : Entity("Wall")
	{
		m_rect = { pos.x, pos.y, pos.w, pos.h };
	}

	void render(SDL_Renderer* renderer);
	void update(float deltaTime) {}
};

