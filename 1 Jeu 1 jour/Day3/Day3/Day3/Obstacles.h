#pragma once
#include "Entity.h"
class Obstacles : public Entity
{
private:

	const float ground = 600.0f - 100.0f;

public:

    Obstacles(Vector2D pos, Vector2D dir, int s)
        : Entity("Obstacle")
    {
        m_rect = { pos.x, pos.y, 20, 20 };
        direction = dir;
        speed = s;
    }

    void render(SDL_Renderer* renderer);
    void update(float deltaTime);
};

