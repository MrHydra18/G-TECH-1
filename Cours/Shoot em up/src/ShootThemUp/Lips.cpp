#include "Lips.h"
#include "Game.h"
#include "Vaisseau.h"
#include "SpaceShip.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Lips::Lips(Vector2D pos, Vector2D dir, float speed, int hp, int maxHp, int width, int height, float bd, std::function<void(Entity*)> OCE)
	: Enemy(pos, dir, speed, hp, maxHp, width, height, bd, OCE)
{
	texture = AssetsManager::getInstance().GetTexture("PixelPack/Enemies/Lips.png");

	numImages = 4;
	currentFrame = 0;
	timeBetweenFrames = 0.1f;
	frameTimer = 0.0f;

	// Limitation de rotation : 25 degrés par seconde
	maxRotationDelta = 25.0f;

	// Récupérer le joueur
	Entity* playerEntity = Game::getInstance()->getEntitieByTag("Player");
	if (playerEntity) {
		player = dynamic_cast<Vaisseau*>(playerEntity);
	} else {
		player = nullptr;

	}
}

Lips::~Lips()
{
	AssetsManager::getInstance().onTextureDelete("PixelPack/Enemies/Lips.png");
}

void Lips::render(SDL_Renderer* renderer)
{
	SDL_Rect sourceRect = { currentFrame * 16, 0, 16, 16 };

	if (texture)
		SDL_RenderCopy(renderer, texture, &sourceRect, &m_rect);
	else
		SDL_RenderDrawRect(renderer, &m_rect);
}

void Lips::update(float deltaTime)
{
	// Animation
	frameTimer += deltaTime;
	if (frameTimer >= timeBetweenFrames)
	{
		frameTimer = 0.0f;
		currentFrame = (currentFrame + 1) % numImages;
	}

	// Tracking du joueur
	if (player) {
		// Utiliser m_rect pour la position de Lips
		Vector2D lipsPos(exactPosition.x, exactPosition.y);

		// Récupérer la position du joueur via le rect
		Vector2D playerPos((float)player->m_rect.x, (float)player->m_rect.y);

		Vector2D toPlayer = playerPos - lipsPos;
		float distanceToPlayer = toPlayer.Magnitude();

		if (distanceToPlayer > 0) {
			// Normaliser la direction vers le joueur
			Vector2D targetDirection = toPlayer / distanceToPlayer;

			// Calculer l'angle actuel et l'angle cible
			float currentAngle = atan2(direction.y, direction.x);
			float targetAngle = atan2(targetDirection.y, targetDirection.x);

			// Calculer la différence d'angle
			float angleDiff = targetAngle - currentAngle;

			// Normaliser la différence d'angle entre -PI et PI
			while (angleDiff > M_PI) angleDiff -= 2 * M_PI;
			while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

			// Limiter la rotation selon maxRotationDelta (convertir en radians)
			float maxRotationRad = (maxRotationDelta * M_PI / 180.0f) * deltaTime;

			if (fabs(angleDiff) > maxRotationRad) {
				// Rotation limitée
				if (angleDiff > 0)
					currentAngle += maxRotationRad;
				else
					currentAngle -= maxRotationRad;
			} else {
				// Rotation directe vers la cible
				currentAngle = targetAngle;
			}

			// Mettre à jour la direction
			direction.x = cos(currentAngle);
			direction.y = sin(currentAngle);
		}
	}

	// Appliquer le mouvement
	Enemy::update(deltaTime);
}
