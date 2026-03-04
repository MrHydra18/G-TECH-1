#include "Mickael.h"
#include "game.h"
#include "Bullet.h"
#include "Mine.h"
#include <cmath>

Mickael::Mickael(Vector2D pos, Vector2D dir, float speed, int hp, int maxHp, int width, int height, float bd, std::function<void(Entity*)> OCE)
	: Enemy(pos, dir, speed, hp, maxHp, width, height, bd, OCE)
{
	texture = AssetsManager::getInstance().GetTexture("Space/Boss.png");
	targetPos = {(float) Game::getInstance()->windowWidth - Game::getInstance()->windowWidth / 5, (float) Game::getInstance()->windowHeight / 2 };
	interShoot = 0.5f;
	lastMine = 0.0f;
	interMine = 1.0f;
}

Mickael::~Mickael()
{
	AssetsManager::getInstance().onTextureDelete("Space/Boss.png");
}

void Mickael::render(SDL_Renderer* renderer)
{
	SDL_Rect sRect = { 0, currentPhase * 128 + 32, 128, 120 };
	SDL_RenderCopyEx(renderer, texture, &sRect, &m_rect, rotation, nullptr, SDL_FLIP_NONE);
}
void Mickael::shoot() {

	if (lastShoot < interShoot)
		return;


	lastShoot = 0.f;

	float rotationRad = rotation * M_PI / 180.0f;

	float centerX = (float)m_rect.x + m_rect.w / 2;
	float centerY = (float)m_rect.y + m_rect.h / 2;

	float halfWidth = m_rect.w / 2.5f;
	float halfHeight = m_rect.h / 2.5f;

	int bulletCount = (currentPhase == 2) ? 8 : 4;

	for (int i = 0; i < bulletCount; i++) {
		float angle = rotationRad + (i * 2.0f * M_PI / bulletCount);

		Vector2D dir = { cos(angle), sin(angle) };

		Vector2D pos = {
			centerX + dir.x * halfWidth,
			centerY + dir.y * halfHeight
		};
		Bullet* b = new BasicBullet("Ebullet", dir, pos, 2, 300.f);
		b->setLayer("Ebullet");
		onCreateEntity(b);
	}
}

void Mickael::placeMine()
{
	if (lastMine < interMine)
		return;

	lastMine = 0.0f;

	int screenWidth = Game::getInstance()->windowWidth;
	int screenHeight = Game::getInstance()->windowHeight;

	Vector2D minePos = {
		(float)(rand() % (screenWidth - 16)),
		(float)(rand() % (screenHeight - 16))
	};

	float lifetime = 2.0f + (float)(rand() % 2000) / 1000.0f;

	Mine* mine = new Mine(minePos, 5, 50.0f, lifetime, onCreateEntity);
	onCreateEntity(mine);
}

void Mickael::updatePhase()
{
	int hpLost = maxhp - hp;

	if (hpLost < 300) {
		currentPhase = 0; 
	}
	else if (hpLost < 600) {
		currentPhase = 1; 
	}
	else {
		currentPhase = 2; 
	}
}

void Mickael::update(float deltaTime)
{
	lastShoot += deltaTime;
	lastMine += deltaTime;


	updatePhase();


	float rotationSpeed = 60.0f;
	float moveSpeed = speed;

	if (currentPhase == 2) {

		rotationSpeed = 120.0f; 
		moveSpeed = speed * 1.5f; 
		interShoot = 0.25f; 
		interMine = .5f;
	}
	else if (currentPhase == 1) {

		interShoot = 0.5f;
		interMine = 1.0f;
	}
	else {
		interShoot = 0.5f;
	}

	rotation += rotationSpeed * deltaTime;
	shoot();

	if (currentPhase >= 1) {
		placeMine();
	}

	Vector2D toTarget = { targetPos.x - exactPosition.x, targetPos.y - exactPosition.y };
	float distance = sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

	if (distance < 10.0f) {
		int screenWidth = Game::getInstance()->windowWidth;
		int screenHeight = Game::getInstance()->windowHeight;
		int rightZoneStart = screenWidth - screenWidth / 5;

		targetPos.x = (float)(rightZoneStart + rand() % (screenWidth - rightZoneStart - m_rect.w));
		targetPos.y = (float)(rand() % (screenHeight - m_rect.h));
	}
	else {

		toTarget.x /= distance;
		toTarget.y /= distance;

		exactPosition.x += toTarget.x * deltaTime * moveSpeed;
		exactPosition.y += toTarget.y * deltaTime * moveSpeed;

		m_rect.x = (int)exactPosition.x;
		m_rect.y = (int)exactPosition.y;
	}
}

