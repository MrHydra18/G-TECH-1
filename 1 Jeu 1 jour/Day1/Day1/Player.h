#pragma once
#include "Entity.h"
#include "SDL.h"

class Player : public Entity
{
private:
    float m_velocityY = 0.0f;
    bool m_isGrounded = false;
    const float m_gravity = 1500.0f;
    const float m_jump = -700.0f;
    const float ground = 600.0f - 75.0f;

public:
    Player(Vector2D pos, Vector2D dir, int s)
        : Entity("Player")
    {
        m_rect = { pos.x, pos.y, 75, 75 };
        direction = dir;
        speed = s;
    }

    void render(SDL_Renderer* renderer);
    void update(float deltaTime);
};