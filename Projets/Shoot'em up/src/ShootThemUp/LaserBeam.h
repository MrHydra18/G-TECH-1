#pragma once
#include "Entity.h"
#include "AssetsManager.h"
#include <vector>

class LaserBeam : public Entity
{
private:
	SDL_Texture* texture;
	int damage;
	float heatLevel;
	std::vector<SDL_Rect> segments;
	int beamWidth;
	int beamHeight;
	float scaleRatioX;
	float scaleRatioY;

public:
	LaserBeam(Vector2D pos, int dmg, float heat, int width, int height, float ratioX = 1.0f, float ratioY = 1.0f);
	~LaserBeam();

	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;

	void setHeatLevel(float heat) { heatLevel = heat; }
	float getHeatLevel() const { return heatLevel; }
	int getDamage() const { return damage; }

	void updatePosition(Vector2D pos, float maxX = -1.0f);

	const std::vector<SDL_Rect>& getSegments() const { return segments; }
};
