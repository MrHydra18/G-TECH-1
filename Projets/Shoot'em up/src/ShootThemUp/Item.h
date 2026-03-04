#pragma once
#include "Entity.h"

class Item : public Entity
{
private:
	SDL_Texture* texture;
	Vector2D exactPosition;
	Vector2D direction;
	float speed;
	int healAmount;

public:
	Item(Vector2D pos, Vector2D dir, float speed, int w, int h, int healAmount = 1);
	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	int getHealAmount() const { return healAmount; }
};