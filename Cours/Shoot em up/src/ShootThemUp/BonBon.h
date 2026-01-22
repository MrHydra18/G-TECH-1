#pragma once
#include "Enemy.h"

class BonBon : public Enemy
{
public:
	BonBon(Vector2D pos, Vector2D dir, float speed, int hp, int maxHp, int width, int height, float bd, std::function<void(Entity*)> OCE);
	~BonBon();
	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;

private:
	int numImages;
	int currentFrame;
	float timeBetweenFrames;
	float frameTimer;

	// Pour le mouvement sinusoïdal
	float waveTime;
	float waveAmplitude;
	float waveFrequency;
	float baseY;
};