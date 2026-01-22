#include "Vaisseau.h"
#include "Enemy.h"
#include "game.h"
#include "BasicBullet.h"
#include "LaserBeam.h"
#include "ExplosiveMissile.h"

Vaisseau::Vaisseau(std::string tag, int width, int height, int HP, int maxHP, float speed, std::function<void(Entity*)> OCE, float bd) : SpaceShip(tag, {50.f, 50.f}, {0.f, 0.f}, speed, HP, maxHP, OCE, bd, width / 3, height)
{
	texture = AssetsManager::getInstance().GetTexture("Spritesheets/Ship.png");
	textureFlame = AssetsManager::getInstance().GetTexture("PixelPack/Ship/Boosters.png");

	// Initialiser la position exacte
	exactPosition = { 50.f, (float) Game::getInstance()->windowHeight / 2 };
	activeLaser = nullptr;
	laserHeat = 0.0f;
	isStunned = false;
	stunTimer = 0.0f;
}

Vaisseau::~Vaisseau()
{
	AssetsManager::getInstance().onTextureDelete("Spritesheets/Ship.png");
	AssetsManager::getInstance().onTextureDelete("PixelPack/Ship/Boosters.png");

	if (activeLaser) {
		delete activeLaser;
		activeLaser = nullptr;
	}
}

void Vaisseau::render(SDL_Renderer* renderer)
{
	
	if (activeLaser) {
		activeLaser->render(renderer);
	}

	SDL_Rect sourceRect = { 16 + direction.y * (16 + 1), 0, 16, 16 };
	if (texture)
	{
		if (isStunned) {
			SDL_SetTextureColorMod(texture, 255, 100, 100);
		}
		SDL_RenderCopyEx(renderer, texture, &sourceRect, &m_rect, 90, nullptr, SDL_FLIP_NONE);
		if (isStunned) {
			SDL_SetTextureColorMod(texture, 255, 255, 255);
		}
	}

	SDL_Rect flamesRect = { m_rect.x - m_rect.w * 1.2f, m_rect.y, m_rect.w, m_rect.h };
	SDL_Rect powerfullFlame = { 0, 0, m_rect.w / 2, m_rect.h };

	if (textureFlame && abs(direction.x) + abs(direction.y) != 0 && !isStunned)
	{
		if (direction.y == 0)
		{
			SDL_Rect bottomRect = { m_rect.x - m_rect.w + m_rect.w / 6, m_rect.y - m_rect.h / 8, powerfullFlame.w, powerfullFlame.h };
			SDL_Rect topRect = { m_rect.x - m_rect.w + m_rect.w / 6, m_rect.y + powerfullFlame.w / 2, powerfullFlame.w, powerfullFlame.h };

			SDL_RenderCopyEx(renderer, textureFlame, &powerfullFlame, &bottomRect, 90, nullptr, SDL_FLIP_NONE);
			SDL_RenderCopyEx(renderer, textureFlame, &powerfullFlame, &topRect, 90, nullptr, SDL_FLIP_NONE);
		}
		else
			SDL_RenderCopyEx(renderer, textureFlame, nullptr, &flamesRect, 90, nullptr, direction.y == 1 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
	}
}

void Vaisseau::update(float deltaTime)
{
	Game* game = Game::getInstance();


	if (isStunned) {
		stunTimer += deltaTime;
		if (stunTimer >= stunDuration) {
			isStunned = false;
			stunTimer = 0.0f;
		}
	}

	if (!isStunned) {
		handleInput();
	}

	
	m_rect.w = game->windowWidth / 50; 
	m_rect.h = game->windowHeight / 23.125f;  

	if (!isStunned) {
		if (abs(direction.x) + abs(direction.y) > 1)
		{
			exactPosition.x += direction.Normalized().x * deltaTime * speed;
			exactPosition.y += direction.Normalized().y * deltaTime * speed;
		}
		else
		{
			exactPosition.x += direction.x * deltaTime * speed;
			exactPosition.y += direction.y * deltaTime * speed;
		}
	}

	exactPosition.x = exactPosition.x < 0 ? 0 : exactPosition.x + m_rect.w > game->windowWidth ? game->windowWidth - m_rect.w : exactPosition.x;
	exactPosition.y = exactPosition.y < 0 ? 0 : exactPosition.y + m_rect.h > game->windowHeight ? game->windowHeight - m_rect.h : exactPosition.y;

	m_rect.x = (int)exactPosition.x;
	m_rect.y = (int)exactPosition.y;

	if (activeLaser) {
		activeLaser->setHeatLevel(laserHeat);
		int laserHeight = (int)(4 * scaleRatioY * 4);
		Vector2D laserPos = { (float)m_rect.x + m_rect.w, (float)m_rect.y};

		std::vector<Entity*> enemies = game->getEntitiesByLayer("enemy");
		float closestEnemyX = (float)game->windowWidth;

		for (auto& enemy : enemies) {
			if (enemy->m_rect.y < laserPos.y + laserHeight &&
				enemy->m_rect.y + enemy->m_rect.h > laserPos.y) {
				if (enemy->m_rect.x > m_rect.x && enemy->m_rect.x < closestEnemyX) {
					closestEnemyX = (float)enemy->m_rect.x;
				}

				for (const auto& segment : activeLaser->getSegments()) {
					if (Entity::checkCollision(segment, enemy->m_rect)) {
						((Enemy*)enemy)->Damage(activeLaser->getDamage() * deltaTime);
						break;
					}
				}
			}
		}

		activeLaser->updatePosition(laserPos, closestEnemyX);
	}
}


bool Vaisseau::handleInput()
{
	InputManager& input = InputManager::getInstance();
	Game* game = Game::getInstance();
	float deltaTime = game->getDeltaTime();

	if (input.IsKeyHeld(SDLK_UP) || input.IsKeyHeld(SDLK_z))
	{
		direction.y = -1;
	}
	if (input.IsKeyHeld(SDLK_DOWN) || input.IsKeyHeld(SDLK_s))
	{
		direction.y = 1;
	}
	if (input.IsKeyHeld(SDLK_LEFT) || input.IsKeyHeld(SDLK_q))
	{
		direction.x = -1;
	}
	if (input.IsKeyHeld(SDLK_RIGHT) || input.IsKeyHeld(SDLK_d))
	{
		direction.x = 1;
	}

	if ((input.IsKeyReleased(SDLK_UP) || input.IsKeyReleased(SDLK_z)) &&
		!input.IsKeyHeld(SDLK_UP) && !input.IsKeyHeld(SDLK_z))
	{
		direction.y = 0;
	}
	if ((input.IsKeyReleased(SDLK_DOWN) || input.IsKeyReleased(SDLK_s)) &&
		!input.IsKeyHeld(SDLK_DOWN) && !input.IsKeyHeld(SDLK_s))
	{
		direction.y = 0;
	}
	if ((input.IsKeyReleased(SDLK_LEFT) || input.IsKeyReleased(SDLK_q)) &&
		!input.IsKeyHeld(SDLK_LEFT) && !input.IsKeyHeld(SDLK_q))
	{
		direction.x = 0;
	}
	if ((input.IsKeyReleased(SDLK_RIGHT) || input.IsKeyReleased(SDLK_d)) &&
		!input.IsKeyHeld(SDLK_RIGHT) && !input.IsKeyHeld(SDLK_d))
	{
		direction.x = 0;
	}

	if (input.IsKeyHeld(SDLK_v)) {
		laserHeat += laserHeatRate * deltaTime;
		if (laserHeat > 1.0f) {
			laserHeat = 1.0f;
			if (!isStunned) {
				isStunned = true;
				stunTimer = 0.0f;
				Damage(50);

				// Créer une explosion sur le joueur
				Vector2D explosionPos = { (float)m_rect.x + m_rect.w / 2, (float)m_rect.y + m_rect.h / 2 };
				ExplosiveMissile* explosion = new ExplosiveMissile("explosion", { 0, 0 }, explosionPos, 0, 0, 100.f);
				explosion->explode();
				explosion->setLayer("effect");
				onCreateEntity(explosion);

				if (activeLaser) {
					delete activeLaser;
					activeLaser = nullptr;
				}
			}
		}

		if (!activeLaser && !isStunned) {
			int laserWidth = (int)(16 * scaleRatioX * 2);
			int laserHeight = (int)(4 * scaleRatioY * 4);
			Vector2D laserPos = { (float)m_rect.x + m_rect.w, (float)m_rect.y};
			int laserDamage = (int)(1000 * damageMultiplier);
			activeLaser = new LaserBeam(laserPos, laserDamage, laserHeat, laserWidth, laserHeight, scaleRatioX, scaleRatioY);
			activeLaser->setLayer("bullet");
		}
	}
	else {
		laserHeat -= laserCooldownRate * deltaTime;
		if (laserHeat < 0.0f) {
			laserHeat = 0.0f;
		}

		if (activeLaser) {
			delete activeLaser;
			activeLaser = nullptr;
		}
	}

	if (input.IsKeyHeld(SDLK_SPACE))
		shoot({ 1.f, 0 }, { (float)m_rect.x + m_rect.w / 2, (float)m_rect.y + m_rect.h / 3 }, 5, 1000.f);

	if (input.IsKeyHeld(SDLK_LCTRL))
		shootMissile({ 1.f, 0 }, { (float)m_rect.x + m_rect.w / 2, (float)m_rect.y + m_rect.h / 3 }, 10, 800.f);

	if (input.IsKeyHeld(SDLK_c))
		shootExplosiveMissile({ 1.f, 0 }, { (float)m_rect.x + m_rect.w / 2, (float)m_rect.y + m_rect.h / 3 }, 15, 600.f, 100.f);

	return true;
}
