#pragma once
#include "Bullet.h"

class Enemy;

class ExplosiveMissile : public Bullet
{
public:
	ExplosiveMissile(std::string tag, Vector2D dir, Vector2D pos, int damage, float s, float explosionRadius, int width = 16, int height = 16);
	~ExplosiveMissile();

	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;

	float getExplosionRadius() const { return explosionRadius; }
	bool hasExploded() const { return exploded; }
	void explode();

private:
	Vector2D exactPosition;
	float explosionRadius; // Rayon de l'explosion
	bool exploded;
	float explosionTimer;
	float explosionDuration;
};
