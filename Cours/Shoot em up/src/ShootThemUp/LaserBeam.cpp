#include "LaserBeam.h"
#include "Game.h"

LaserBeam::LaserBeam(Vector2D pos, int dmg, float heat, int width, int height, float ratioX, float ratioY)
	: Entity("laser"), damage(dmg), heatLevel(heat), beamWidth(width), beamHeight(height), scaleRatioX(ratioX), scaleRatioY(ratioY)
{
	texture = AssetsManager::getInstance().GetTexture("Space/Bullets.png");
	m_rect = { (int)pos.x, (int)pos.y - height, width, height };
	direction = { 1.f, 0.f };

	Game* game = Game::getInstance();
	int screenWidth = game->windowWidth;
	int segmentSize = 16;

	segments.clear();
	for (int x = (int)pos.x; x < screenWidth; x += beamWidth) {
		SDL_Rect segment = { x, (int)pos.y, 100, 100 };
		segments.push_back(segment);
	}
}

LaserBeam::~LaserBeam()
{
	AssetsManager::getInstance().onTextureDelete("Space/Bullets.png");
}

void LaserBeam::render(SDL_Renderer* renderer)
{
	SDL_Rect sourceRect;
	if (heatLevel < 0.33f) {
		sourceRect = { 240, 224, 16, 16 }; 
	}
	else if (heatLevel < 0.66f) {
		sourceRect = { 240, 192, 16, 16 };
	}
	else {
		sourceRect = { 240, 160, 16, 16 };
	}

	for (const auto& segment : segments) {
		SDL_RenderCopyEx(renderer, texture, &sourceRect, &segment, 90, 0, SDL_FLIP_NONE);
	}
	sourceRect.x -= 16;
	if (segments.empty())
		return;
	SDL_Rect endRect = segments.back();
	endRect.x += beamWidth / 2;
	SDL_RenderCopyEx(renderer, texture, &sourceRect, &endRect, 0, 0, SDL_FLIP_NONE);
}

void LaserBeam::update(float deltaTime)
{
	//decla vide c'est le player qui gere
}

void LaserBeam::updatePosition(Vector2D pos, float maxX)
{
	Game* game = Game::getInstance();
	int screenWidth = game->windowWidth;

	if (maxX > 0.0f && maxX < screenWidth) {
		screenWidth = (int)maxX;
	}

	segments.clear();
	for (int x = (int)pos.x; x < screenWidth; x += beamWidth) {
		SDL_Rect segment = { x, (int)pos.y, beamHeight, beamWidth };
		segments.push_back(segment);
	}

	m_rect.x = (int)pos.x;
	m_rect.y = (int)pos.y;
}
