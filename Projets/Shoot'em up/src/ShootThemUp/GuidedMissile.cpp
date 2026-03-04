#include "GuidedMissile.h"
#include "Game.h"
#include "Enemy.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

GuidedMissile::GuidedMissile(std::string tag, Vector2D dir, Vector2D pos, int damage, float s, int width, int height)
	: Bullet(pos, dir, s, damage, width, height)
{
	texture = AssetsManager::getInstance().GetTexture("Space/Bullets.png");
	direction = dir;
	m_rect.x = pos.x;
	m_rect.y = pos.y;
	m_rect.w = width;
	m_rect.h = height;

	exactPosition = pos;
	target = nullptr;
	maxRotationDelta = 180.0f;
}

GuidedMissile::~GuidedMissile()
{
	AssetsManager::getInstance().onTextureDelete("Space/Bullets.png");
}

void GuidedMissile::render(SDL_Renderer* renderer)
{
	SDL_Rect sourceRect = { 16, 80, 16, 16 };
	SDL_RenderCopy(renderer, texture, &sourceRect, &m_rect);
}

Enemy* GuidedMissile::findClosestEnemy()
{
	Game* game = Game::getInstance();
	std::vector<Entity*> enemies = game->getEntitiesByLayer("enemy");

	Enemy* closest = nullptr;
	float minDistance = FLT_MAX;

	for (auto& entity : enemies) {
		Enemy* enemy = (Enemy*)entity;
		if (!enemy->markedForDeletion) {
			Vector2D missilePos(exactPosition.x, exactPosition.y);
			Vector2D enemyPos((float)enemy->m_rect.x, (float)enemy->m_rect.y);
			Vector2D toEnemy = enemyPos - missilePos;
			float distance = toEnemy.Magnitude();

			if (distance < minDistance) {
				minDistance = distance;
				closest = enemy;
			}
		}
	}

	return closest;
}

void GuidedMissile::update(float deltaTime)
{
	if (!target || target->markedForDeletion) {
		target = findClosestEnemy();
	}

	if (target) {
		Vector2D missilePos(exactPosition.x, exactPosition.y);
		Vector2D targetPos((float)target->m_rect.x, (float)target->m_rect.y);

		Vector2D toTarget = targetPos - missilePos;
		float distanceToTarget = toTarget.Magnitude();

		if (distanceToTarget > 0) {
			Vector2D targetDirection = toTarget / distanceToTarget;

			float currentAngle = atan2(direction.y, direction.x);
			float targetAngle = atan2(targetDirection.y, targetDirection.x);

			float angleDiff = targetAngle - currentAngle;

			while (angleDiff > M_PI) angleDiff -= 2 * M_PI;
			while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

			float maxRotationRad = (maxRotationDelta * M_PI / 180.0f) * deltaTime;

			if (fabs(angleDiff) > maxRotationRad) {
				if (angleDiff > 0)
					currentAngle += maxRotationRad;
				else
					currentAngle -= maxRotationRad;
			} else {
				currentAngle = targetAngle;
			}

			direction.x = cos(currentAngle);
			direction.y = sin(currentAngle);
		}
	}

	exactPosition.x += direction.x * deltaTime * speed;
	exactPosition.y += direction.y * deltaTime * speed;

	m_rect.x = (int)exactPosition.x;
	m_rect.y = (int)exactPosition.y;
}
