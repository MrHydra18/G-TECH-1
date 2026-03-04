#pragma once

#include "Enemy.h"



class Mickael : public Enemy {

	int currentPhase = 0;
	int currentAngle = 0;


	Vector2D targetPos;

	float lastShoot;
	float interShoot;
	float lastMine;
	float interMine;

public:
	Mickael(Vector2D pos, Vector2D dir, float speed, int hp, int maxHp, int width, int height, float bd, std::function<void(Entity*)> OCE);
	~Mickael();
	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void shoot();
	void placeMine();
	void updatePhase();
	bool isBoss() const { return true; }

};