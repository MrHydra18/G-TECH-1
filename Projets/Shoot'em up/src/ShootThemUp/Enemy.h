#pragma once
#include "SpaceShip.h"

class Enemy : public SpaceShip {

protected:
	Vector2D exactPosition = { 0, 0 };
	float dropChance = 0.1f;

public:
	Enemy(Vector2D pos, Vector2D dir, float s, int HP, int mh, int w, int h, float bd, std::function<void(Entity*)> OEC)
		: SpaceShip("Enemy", pos, dir, s, HP, mh, OEC, bd, w, h) {
		setLayer("enemy");
		exactPosition = pos;
	}

	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	virtual bool isBoss() const { return false; }

	void replaceEntityAfterWindowResize(int oldWidth, int oldHeight, int newWidth, int newHeight) override {
		SpaceShip::replaceEntityAfterWindowResize(oldWidth, oldHeight, newWidth, newHeight);

		// Mettre à jour aussi exactPosition
		float ratioX = (float)newWidth / oldWidth;
		float ratioY = (float)newHeight / oldHeight;
		exactPosition.x = exactPosition.x * ratioX;
		exactPosition.y = exactPosition.y * ratioY;
	}

	float getDropChance() const { return dropChance; }
	void setDropChance(float chance) { dropChance = chance; }
};