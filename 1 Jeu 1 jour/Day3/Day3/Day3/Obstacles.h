#pragma once
#include "Entity.h"
class Obstacles : public Entity
{
private:

	const float ground = 600.0f - 100.0f;

public:

    Obstacles(Vector2D pos) : Entity("Obstacle")
    {
        m_rect = { pos.x, pos.y, 75, 75 };
    }

    void render(SDL_Renderer* renderer);
    void update(float deltaTime);
};

