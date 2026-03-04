#pragma once
#include "Bullet.h"

class BasicBullet : public Bullet
{
public:

	BasicBullet(std::string tag, Vector2D dir, Vector2D pos, int damage, float s, int width = 16, int height = 12) : Bullet(pos, dir, s, damage, width, height)
	{
		texture = AssetsManager::getInstance().GetTexture("Space/Bullets.png");
		direction = dir;
		m_rect.x = pos.x;
		m_rect.y = pos.y;
		m_rect.w = width;
		m_rect.h = height;
	}

	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
};