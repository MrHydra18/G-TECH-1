#pragma once
#include "Vector2D.h"
#include "SDL.h"


class Entity
{

public:

	std::string tag;
	Vector2D direction;
	SDL_FRect m_rect{ 100, 100, 50, 50 };
	float m_spawn = 0.0f;

	Entity(std::string t) : tag(t) {}

	std::string getTag() const { return tag; }
	Vector2D getPosition() const { return Vector2D((float)m_rect.x, (float)m_rect.y); }


	void setPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f) {
		m_rect.x = (int)(x - m_rect.w * anchorX);
		m_rect.y = (int)(y - m_rect.h * anchorY);
	}

	bool collision(SDL_FRect other);
	bool isInside(Vector2D pos);


	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void update(float deltaTime) = 0;
};

