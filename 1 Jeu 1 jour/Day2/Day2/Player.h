#pragma once
#include "Entity.h"
#include "SDL.h"

class Player : public Entity
{

public:
    Player(Vector2D pos, Vector2D dir, int s)
        : Entity("Player")
    {
        m_rect = { pos.x, pos.y, 50, 50 };
        direction = dir;
        speed = s;
    }

    void render(SDL_Renderer* renderer);
    void update(float deltaTime);
};