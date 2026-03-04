#pragma once
#include "Entity.h"

class Bullet : public Entity {

protected:
	float speed;
	int damage;



public:
	Bullet(Vector2D pos, Vector2D dir, int s, int dmg, int width, int height) : Entity("bullet"), speed(s), damage(dmg) {
		m_rect = { (int)pos.x, (int)pos.y, width, height };
		direction = dir;
	}

	int getDamage() { return damage; }

	virtual void update(float deltaTime) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
};

