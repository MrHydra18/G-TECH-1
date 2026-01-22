#include "ExplosiveMissile.h"
#include "Game.h"
#include "Enemy.h"
#include <cmath>

ExplosiveMissile::ExplosiveMissile(std::string tag, Vector2D dir, Vector2D pos, int damage, float s, float expRadius, int width, int height)
	: Bullet(pos, dir, s, damage, width, height)
{
	texture = AssetsManager::getInstance().GetTexture("Space/Bullets.png");
	direction = dir;
	m_rect.x = pos.x;
	m_rect.y = pos.y;
	m_rect.w = width;
	m_rect.h = height;

	exactPosition = pos;
	explosionRadius = expRadius;
	exploded = false;
	explosionTimer = 0.0f;
	explosionDuration = 0.2f; // Durée de l'animation d'explosion
}

ExplosiveMissile::~ExplosiveMissile()
{
	AssetsManager::getInstance().onTextureDelete("Space/Bullets.png");
}

void ExplosiveMissile::render(SDL_Renderer* renderer)
{
	if (!exploded) {
		// Missile normal
		SDL_Rect sourceRect = { 16, 112, 16, 16 };
		SDL_RenderCopy(renderer, texture, &sourceRect, &m_rect);
	} else {
		// Animation d'explosion (cercle qui grandit)
		float progress = explosionTimer / explosionDuration;
		int currentRadius = (int)(explosionRadius * progress);

		// Dessiner un cercle d'explosion (approximation avec des lignes)
		SDL_SetRenderDrawColor(renderer, 255, 100, 0, 200); // Orange
		for (int w = 0; w < currentRadius * 2; w++) {
			for (int h = 0; h < currentRadius * 2; h++) {
				int dx = currentRadius - w;
				int dy = currentRadius - h;
				if ((dx*dx + dy*dy) <= (currentRadius * currentRadius)) {
					SDL_RenderDrawPoint(renderer, m_rect.x + m_rect.w/2 + dx, m_rect.y + m_rect.h/2 + dy);
				}
			}
		}
	}
}

void ExplosiveMissile::explode()
{
	if (exploded) return;

	exploded = true;
	explosionTimer = 0.0f;

	// Infliger des dégâts à tous les ennemis dans le rayon d'explosion
	Game* game = Game::getInstance();
	std::vector<Entity*> enemies = game->getEntitiesByLayer("enemy");

	Vector2D explosionPos(exactPosition.x + m_rect.w / 2, exactPosition.y + m_rect.h / 2);

	for (auto& entity : enemies) {
		Enemy* enemy = (Enemy*)entity;
		if (!enemy->markedForDeletion) {
			Vector2D enemyPos((float)enemy->m_rect.x + enemy->m_rect.w / 2,
			                  (float)enemy->m_rect.y + enemy->m_rect.h / 2);

			Vector2D toEnemy = enemyPos - explosionPos;
			float distance = toEnemy.Magnitude();

			// Si l'ennemi est dans le rayon d'explosion
			if (distance <= explosionRadius) {
				enemy->Damage(damage);
			}
		}
	}

	// Jouer le son d'explosion
	AudioManager::getInstance().playSound("Boom");
}

void ExplosiveMissile::update(float deltaTime)
{
	if (exploded) {
		// Animation d'explosion
		explosionTimer += deltaTime;
		if (explosionTimer >= explosionDuration) {
			markedForDeletion = true;
		}
		return;
	}

	// Mouvement normal du missile
	exactPosition.x += direction.x * deltaTime * speed;
	exactPosition.y += direction.y * deltaTime * speed;

	m_rect.x = (int)exactPosition.x;
	m_rect.y = (int)exactPosition.y;
}
