#pragma once
#include "Enemy.h"

class Alan : public Enemy
{
public:
	Alan(Vector2D pos, Vector2D dir, float speed, int hp, int maxHp, int width, int height, float bd, std::function<void(Entity*)> OCE);
	~Alan();
	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;

private:
	int numImages;
	int currentFrame;
	float timeBetweenFrames;
	float frameTimer;
	Uint32 lastFrameTime;
};