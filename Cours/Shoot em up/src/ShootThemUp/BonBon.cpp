#include "BonBon.h"
#include <cmath>

BonBon::BonBon(Vector2D pos, Vector2D dir, float speed, int hp, int maxHp, int width, int height, float bd, std::function<void(Entity*)> OCE)
	: Enemy(pos, dir, speed, hp, maxHp, width, height, bd, OCE)
{
	texture = AssetsManager::getInstance().GetTexture("PixelPack/Enemies/Bon_Bon.png");

	numImages = 4;
	currentFrame = 0;
	timeBetweenFrames = 0.15f;
	frameTimer = 0.0f;

	// Mouvement sinusoïdal
	waveTime = 0.0f;
	waveAmplitude = 50.0f;
	waveFrequency = 2.0f;
	baseY = pos.y;
}

BonBon::~BonBon()
{
	AssetsManager::getInstance().onTextureDelete("PixelPack/Enemies/Bon_Bon.png");
}

void BonBon::render(SDL_Renderer* renderer)
{
	SDL_Rect sourceRect = { currentFrame * 16, 0, 16, 16 };

	if (texture)
		SDL_RenderCopy(renderer, texture, &sourceRect, &m_rect);
	else
		SDL_RenderDrawRect(renderer, &m_rect);
}

void BonBon::update(float deltaTime)
{
	// Animation des frames
	frameTimer += deltaTime;
	if (frameTimer >= timeBetweenFrames)
	{
		frameTimer = 0.0f;
		currentFrame = (currentFrame + 1) % numImages;
	}

	// Mouvement sinusoïdal
	waveTime += deltaTime;
	float offsetY = sin(waveTime * waveFrequency) * waveAmplitude;

	// Appliquer le mouvement horizontal (Enemy::update)
	Enemy::update(deltaTime);

	// Ajouter l'ondulation verticale
	exactPosition.y = baseY + offsetY;
	m_rect.y = (int)exactPosition.y;
}
