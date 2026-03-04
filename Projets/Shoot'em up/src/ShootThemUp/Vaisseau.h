#pragma once
#include"SpaceShip.h"
#include"InputManager.h"


class Vaisseau : public SpaceShip
{
private:

	SDL_Texture* textureFlame;
	Vector2D exactPosition = {50.f, 50.f};  // Position précise en float

	// tout le laser 
	LaserBeam* activeLaser = nullptr;
	float laserHeat = 0.0f; 
	float laserHeatRate = 0.3f; 
	float laserCooldownRate = 0.5f;
	bool isStunned = false;
	float stunTimer = 0.0f;
	float stunDuration = 2.0f; 


public:

	Vaisseau(std::string tag, int width, int height, int HP, int maxHP, float speed, std::function<void(Entity*)> OCE, float bd);
	~Vaisseau();
	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;

	void replaceEntityAfterWindowResize(int oldWidth, int oldHeight, int newWidth, int newHeight) override {
		SpaceShip::replaceEntityAfterWindowResize(oldWidth, oldHeight, newWidth, newHeight);

		float ratioX = (float)newWidth / oldWidth;
		float ratioY = (float)newHeight / oldHeight;
		exactPosition.x = exactPosition.x * ratioX;
		exactPosition.y = exactPosition.y * ratioY;
	}

	void setSpeed(float s) { speed = s; }
	void setMaxHp(int newMaxHp) { maxhp = newMaxHp; }
	void setHp(int newHp) { hp = newHp; }
	void setBulletDelay(float delay) { bulletDelay = delay; }

	bool handleInput();
};

