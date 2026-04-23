#include "Player.h"
#include "InputManager.h"

void Player::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRectF(renderer, &m_rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 285, 255);
    SDL_RenderDrawRectF(renderer, &m_rect);
}

void Player::update(float deltaTime)
{
    InputManager& input = InputManager::getInstance();

    float velX = 0.0f;
    float velY = 0.0f;

    if (input.IsKeyHeld(SDLK_q) || input.IsKeyHeld(SDLK_LEFT))
        velX -= 1;
    if (input.IsKeyHeld(SDLK_d) || input.IsKeyHeld(SDLK_RIGHT))
        velX += 1;
    if (input.IsKeyHeld(SDLK_z) || input.IsKeyHeld(SDLK_UP))
        velY -= 1;
    if (input.IsKeyHeld(SDLK_s) || input.IsKeyHeld(SDLK_DOWN))
        velY += 1;

    m_rect.x += velX * speed * deltaTime;
    m_rect.y += velY * speed * deltaTime;

    if (m_rect.y + m_rect.h >= 600)
    {
        m_rect.y  = 550;
    }

    if (m_rect.x < 0) m_rect.x = 0;
    if (m_rect.x + m_rect.w > 1000) m_rect.x = 1000 - m_rect.w;

    if (m_rect.y <= 0)
    {
        m_rect.y = 0;
    }
}