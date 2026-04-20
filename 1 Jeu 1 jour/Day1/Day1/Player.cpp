#include "Player.h"
#include "InputManager.h"

void Player::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRectF(renderer, &m_rect);
}

void Player::update(float deltaTime)
{
    InputManager& input = InputManager::getInstance();

    float velX = 0.0f;
    if (input.IsKeyHeld(SDLK_q) || input.IsKeyHeld(SDLK_LEFT))
        velX -= 1;
    if (input.IsKeyHeld(SDLK_d) || input.IsKeyHeld(SDLK_RIGHT))
        velX += 1;

    m_rect.x += velX * speed * deltaTime;

    if (input.IsKeyDown(SDLK_SPACE) && m_isGrounded)
    {
        m_velocityY = m_jump;
        m_isGrounded = false;
    }

    m_velocityY += m_gravity * deltaTime;
    m_rect.y += m_velocityY * deltaTime;

    if (m_rect.y >= ground)
    {
        m_rect.y = ground;
        m_velocityY = 0.0f;
        m_isGrounded = true;
    }

    if (m_rect.x < 0) m_rect.x = 0;
    if (m_rect.x + m_rect.w > 1000) m_rect.x = 1000 - m_rect.w;

    if (m_rect.y < 0)
    {
        m_rect.y = 0;
        m_velocityY = 0.0f;
    }
}