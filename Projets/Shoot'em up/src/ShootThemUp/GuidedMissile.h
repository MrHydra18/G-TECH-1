#pragma once
#include "Bullet.h"

class Enemy;

class GuidedMissile : public Bullet
{
public:
	GuidedMissile(std::string tag, Vector2D dir, Vector2D pos, int damage, float s, int width = 16, int height = 12);
	~GuidedMissile();

	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;

private:
	Vector2D exactPosition;
	Enemy* target;
	float maxRotationDelta; 

	Enemy* findClosestEnemy();
};
