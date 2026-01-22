#include "Alan.h"
#include "BonBon.h"
#include "Lips.h"
#include "ExplosiveMissile.h"
#include "LaserBeam.h"
#include "Mine.h"
#include "Game.h"
#include "Menus.h"
#include "InputManager.h"
#include "Entity.h"
#include "ParalaxManager.h"
#include "Bullet.h"
#include "AudioManager.h"
#include "ShopMenu.h"
#include "Mickael.h"
#include "GameOverMenu.h"
#include "WinMenu.h"


Game::Game(int width, int height)
	: window(nullptr), renderer(nullptr), isRunning(false),
	windowWidth(width), windowHeight(height), lastTime(0) {
	inputManager = &InputManager::getInstance();
	inputManager->SetOnFocusLostCb([this] {
		inputManager->resetKey(SDLK_ESCAPE);
		setState(GameState::Paused);
		UIManager::getInstance().pushMenu(new PauseMenu(renderer, this));

		});
	paralaxManager = &ParalaxManager::getInstance();
	srand(time(NULL));
	originalWidth = width;
	originalHeight = height;
}

Game::~Game() {
	clean();
}

void Game::setLevel(LevelData* newLevel)
{

	Vaisseau* player = new Vaisseau("Player", 32, 32, playerMaxHeath, playerMaxHeath, playerSpeed, [this](Entity* e) {addEntity(e); }, playerBulletCooldown);
	player->damageMultiplier = playerDamageMultiplicator;
	addEntity(player);
	currentLevel = newLevel;
	actualWave = 0;
	timebetweenWaves = currentLevel->time / currentLevel->columns;
	lastSpawn = SDL_GetTicks();
	AudioManager::getInstance().playSound("LaunchLevel");
	currentState = GameState::Playing;
	secondesinceLevelStart = 0.f;
}

void Game::resetLevel()
{
	clearEntity();
	currentLevel = nullptr;
	bossFight = false;
}

bool Game::init(std::string name, int x, int y, bool fullScreen) {


	window = SDL_CreateWindow(name.c_str(), x, y, windowWidth, windowHeight, fullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE);
	if (!window) {
		return false;
	}

	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		return false;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// Initialiser l'AssetsManager avec le renderer
	AssetsManager::getInstance().init(renderer);

	// Initialiser l'UIManager avec le renderer (gère TTF en interne)
	UIManager::getInstance().init(renderer);

	paralaxManager->setGame(this);
	paralaxManager->setPath("Paralaxs/");
	paralaxManager->resetParalax();

	lastTime = SDL_GetTicks();
	isRunning = true;

	UIManager::getInstance().pushMenu(new MainMenu(renderer, this));

	AudioManager::getInstance().init();
	if (!init_sound()) {
		std::cerr << "[Game] Error while loading sounds for AudioManager\n";
	}
	return true;
}

bool Game::init_sound()
{

	//troll sound
	AudioManager::getInstance().loadSound("Achat", { "Achat.wav", "Achat2.wav", "Achat3.wav", "Achat4.wav", "Achat5.wav", "Achat6.wav" });
	AudioManager::getInstance().loadSound("Boom", { "boom.wav", "boom2.wav", "boom3.wav", "boom4.wav", "boom5.wav", "boom6.wav", "boom7.wav", "boom8.wav", "boom9.wav", "boom10.wav", "boom11.wav", "boom12.wav", "boom13.wav", "boom14.wav" });
	AudioManager::getInstance().loadSound("Boss", { "Boss.wav", "Boss2.wav", "Boss3.wav", "Boss4.wav" });
	AudioManager::getInstance().loadSound("Button", { "confirmation.wav" });
	AudioManager::getInstance().loadSound("Degat", { "Degats.wav", "Degats2.wav" , "Degats3.wav" , "Degats4.wav" , "Degats5.wav" , "Degats6.wav" , "degat7.wav" });
	AudioManager::getInstance().loadSound("OnMenuEnter", { "enterOnMenu.wav", "enterOnMenu2.wav" , "enterOnMenu3.wav" });
	AudioManager::getInstance().loadSound("Kill", { "kill.wav", "kill2.wav" , "kill3.wav" , "kill4.wav" });
	AudioManager::getInstance().loadSound("LaunchLevel", { "LunchLevel.wav", "LunchLevel2.wav" , "LunchLevel3.wav" , "LunchLevel4.wav" , "LunchLevel5.wav" });
	AudioManager::getInstance().loadSound("Dead", { "mort.wav", "mort2.wav" , "mort3.wav" , "mort4.wav" , "mort5.wav" , "mort6.wav" , "mort7.wav" });
	AudioManager::getInstance().loadSound("Shoot", { "normalBulletShoot.wav", "normalBulletShoot2.wav" , "normalBulletShoot3.wav" , "normalBulletShoot4.wav" , "normalBulletShoot5.wav" });
	AudioManager::getInstance().loadSound("Quit", { "quit.wav", "quit2.wav", "quit3.wav" });
	AudioManager::getInstance().loadSound("Save", { "Save.wav" });
	AudioManager::getInstance().loadSound("Win", { "win.wav","win2.wav" ,"win3.wav" ,"win4.wav" });

	//music de fond
	AudioManager::getInstance().loadMusic("Music1", "musicDeFond.ogg");
	AudioManager::getInstance().loadMusic("Music2", "musicDeFond2.ogg");

	AudioManager::getInstance().playMusic("Music1");
	return true;
}

void Game::handleEvents() {
	isRunning = inputManager->update();


	if (inputManager->IsKeyDown(SDLK_ESCAPE) && currentState == GameState::Playing) {
		inputManager->resetKey(SDLK_ESCAPE);
		setState(GameState::Paused);
		UIManager::getInstance().pushMenu(new PauseMenu(renderer, this));
	}

	if (UIManager::getInstance().hasMenus())
		UIManager::getInstance().handleInput();



	if (inputManager->windowResized) {
		for (auto& entity : entities) {
			entity->replaceEntityAfterWindowResize(windowWidth, windowHeight, inputManager->newWidth, inputManager->newHeight);
		}

		scaleRatioX = (float)inputManager->newWidth / (float)originalWidth;
		scaleRatioY = (float)inputManager->newHeight / (float)originalHeight;

		Entity* player = getEntitieByTag("Player");
		if (player) {
			((Vaisseau*)player)->setScaleRatios(scaleRatioX, scaleRatioY);
		}

		std::vector<Entity*> enemies = getEntitiesByLayer("enemy");
		for (auto& enemy : enemies) {
			((SpaceShip*)enemy)->setScaleRatios(scaleRatioX, scaleRatioY);
		}


		windowWidth = inputManager->newWidth;
		windowHeight = inputManager->newHeight;

		scaleRatioX = (float)windowWidth / (float)originalWidth;
		scaleRatioY = (float)windowHeight / (float)originalHeight;

		inputManager->windowResized = false;
	}

}

void Game::UpdateSpawnEntity(float dt)
{
	if (currentLevel == nullptr)
		return;

	if (currentState != GameState::Playing)
		return;

	if (bossFight)
		return;

	spawnCooldown -= dt * 1000;
	if (spawnCooldown > 0)
		return;

	spawnCooldown += timebetweenWaves;

	for (int row = 0; row < currentLevel->rows; row++)
	{
		switch (currentLevel->get(row, actualWave))
		{
		case (1): // Alan
		{
			int scaledWidth = (int)(32 * scaleRatioX);
			int scaledHeight = (int)(32 * scaleRatioY);
			float scaledSpeed = 150.f * scaleRatioX;

			Vector2D position(windowWidth, row * (windowHeight / currentLevel->rows));
			Vector2D direction(-1, 0);

			Alan* a = new Alan(position, direction, scaledSpeed, 2, 2, scaledWidth, scaledHeight, 5000.f, [this](Entity* e) {addEntity(e); });
			a->setScaleRatios(scaleRatioX, scaleRatioY);
			a->setDropChance(0.1f);
			addEntity(a);
			break;
		}
		case (2): // BonBon
		{
			int scaledWidth = (int)(32 * scaleRatioX);
			int scaledHeight = (int)(32 * scaleRatioY);
			float scaledSpeed = 100.f * scaleRatioX;

			Vector2D position(windowWidth, row * (windowHeight / currentLevel->rows));
			Vector2D direction(-1, 0);

			BonBon* b = new BonBon(position, direction, scaledSpeed, 1, 1, scaledWidth, scaledHeight, 5000.f, [this](Entity* e) {addEntity(e); });
			b->setScaleRatios(scaleRatioX, scaleRatioY);
			b->setDropChance(0.2f);
			addEntity(b);
			break;
		}
		case (3): // Lips
		{
			int scaledWidth = (int)(32 * scaleRatioX);
			int scaledHeight = (int)(32 * scaleRatioY);
			float scaledSpeed = 560.f * scaleRatioX;

			Vector2D position(windowWidth, row * (windowHeight / currentLevel->rows));
			Vector2D direction(-1, 0);

			Lips* l = new Lips(position, direction, scaledSpeed, 3, 3, scaledWidth, scaledHeight, 5000.f, [this](Entity* e) {addEntity(e); });
			l->setScaleRatios(scaleRatioX, scaleRatioY);
			l->setDropChance(0.2f);
			addEntity(l);
			break;
		}
		case(7): // Mickael
		{
			int scaledWidth = (int)(128 * scaleRatioX);
			int scaledHeight = (int)(128 * scaleRatioY);
			float scaledSpeed = 100.f * scaleRatioX;

			Vector2D position(windowWidth, row * (windowHeight / currentLevel->rows));
			Vector2D direction(-1, 0);

			Mickael* m = new Mickael(position, direction, scaledSpeed, 900, 900, scaledWidth, scaledHeight, 5000.f, [this](Entity* e) {addEntity(e); });
			m->setScaleRatios(scaleRatioX, scaleRatioY);
			m->setDropChance(0.5f);
			addEntity(m);
			bossFight = true;
			actualWave++;
			return;
			break;
		}
		default:
			break;
		}
	}

	actualWave++;
}

void Game::dropItemFromEnemy(Enemy* enemy)
{
	float randomValue = (float)rand() / RAND_MAX;

	if (randomValue <= enemy->getDropChance())
	{
		int scaledWidth = (int)(24 * scaleRatioX);
		int scaledHeight = (int)(24 * scaleRatioY);
		float scaledSpeed = 100.f * scaleRatioX;

		Vector2D itemPos(enemy->m_rect.x, enemy->m_rect.y);
		Vector2D itemDir(-1, 0);

		Item* item = new Item(itemPos, itemDir, scaledSpeed, scaledWidth, scaledHeight, 5);
		addEntity(item);
	}
}

void Game::update(float deltaTime) {

	for (auto& entity : entitiesToAdd) {
		entities.push_back(entity);
	}

	entitiesToAdd.clear();
	paralaxManager->update(deltaTime);

	if (UIManager::getInstance().hasMenus())
	{
		UIManager::getInstance().update(deltaTime);
	}
	else
	{
		secondesinceLevelStart += deltaTime;
		std::vector<Entity*> bullets = getEntitiesByLayer("bullet");
		std::vector<Entity*> enemys = getEntitiesByLayer("enemy");
		std::vector<Entity*> mines = getEntitiesByLayer("mine");
		Entity* player = getEntitieByTag("Player");
		std::vector<Entity*> items = getEntitiesByLayer("item");

		if (secondesinceLevelStart >= 60.f && enemys.size() <= 0) {
			UIManager::getInstance().pushMenu(new WinMenu(renderer, this));
			return;
		}

		for (auto& bullet : bullets)
		{
			LaserBeam* laser = dynamic_cast<LaserBeam*>(bullet);

			for (auto& mineEntity : mines)
			{
				if (mineEntity->markedForDeletion) continue;

				bool hasCollision = false;

				if (laser) {
					for (const auto& segment : laser->getSegments()) {
						if (Entity::checkCollision(segment, mineEntity->m_rect)) {
							hasCollision = true;
							break;
						}
					}
				}
				else {
					hasCollision = bullet->collision(mineEntity->m_rect);
				}

				if (hasCollision)
				{
					Mine* mine = (Mine*)mineEntity;
					if (!mine->hasExploded()) {
						mine->explode(true);
					}

					if (!laser) {
						bullet->markedForDeletion = true;
					}
					break;
				}
			}
		}



		for (auto& bullet : bullets)
		{
			ExplosiveMissile* explosiveMissile = dynamic_cast<ExplosiveMissile*>(bullet);
			LaserBeam* laser = dynamic_cast<LaserBeam*>(bullet);

			for (auto& enemy : enemys)
			{
				bool hasCollision = false;

				if (laser) {
					for (const auto& segment : laser->getSegments()) {
						if (Entity::checkCollision(segment, enemy->m_rect)) {
							hasCollision = true;
							break;
						}
					}
				}
				else {
					hasCollision = bullet->collision(enemy->m_rect);
				}

				if (hasCollision)
				{
					if (explosiveMissile && !explosiveMissile->hasExploded()) {
						explosiveMissile->explode();
					}
					else if (laser) {
						((Enemy*)enemy)->Damage(((LaserBeam*)bullet)->getDamage());
					}
					else {
						((Enemy*)enemy)->Damage(((Bullet*)bullet)->getDamage());
						AudioManager::getInstance().playSound("Boom");
						bullet->markedForDeletion = true;
					}

					if (((Enemy*)enemy)->getHp() <= 0)
					{
						Enemy* e = (Enemy*)enemy;

						if (!e->isBoss()) {
							dropItemFromEnemy(e);
							addPlayerMoney(5);
						}
						else if (e->isBoss()) {
							bossFight = false;
							addPlayerMoney(100);
						}
					}
				}
			}
		}

		if (!player) {
			UIManager::getInstance().pushMenu(new GameOverMenu(renderer, this));
			return;
		}



		for (auto& enemy : enemys) {
			if (!enemy->markedForDeletion && player->collision(enemy->m_rect)) {
				Enemy* e = (Enemy*)enemy;

				if (e->isBoss()) {
					((Vaisseau*)player)->Damage(deltaTime);
				}
				else {
					((Vaisseau*)player)->Damage(1);
					e->Damage(e->getHp());
					AudioManager::getInstance().playSound("Boom");
				}
			}
		}

		for (auto& Ebullet : getEntitiesByLayer("Ebullet")) {
			if (player->collision(Ebullet->m_rect)) {
				Ebullet->markedForDeletion = true;
				((Vaisseau*)player)->Damage(((Bullet*)Ebullet)->getDamage());
			}
		}

		for (auto& enemy : enemys) {
			if (enemy->m_rect.x + enemy->m_rect.w <= 0 && !enemy->markedForDeletion) {
				Lips* lips = dynamic_cast<Lips*>(enemy);
				if (!lips) {
					((Vaisseau*)player)->Damage(1);
					enemy->markedForDeletion = true;
				}
			}
		}


		for (auto& entity : entities) {
			if (!entity->markedForDeletion) {
				entity->update(deltaTime);
			}
		}


		for (auto& enemy : enemys) {
			if (enemy->m_rect.x + enemy->m_rect.w <= 0 && !enemy->markedForDeletion) {
				Lips* lips = dynamic_cast<Lips*>(enemy);
				if (!lips) {
					((Vaisseau*)player)->Damage(1);
					enemy->markedForDeletion = true;
				}
			}
		}



		for (auto& item : items)
		{
			if (!item->markedForDeletion && player->collision(item->m_rect))
			{
				Item* healItem = (Item*)item;
				Vaisseau* vaisseau = (Vaisseau*)player;

				int currentHp = vaisseau->getHp();
				int maxHp = vaisseau->getMaxHp();
				int newHp = std::min(currentHp + healItem->getHealAmount(), maxHp);

				vaisseau->setHp(newHp);

				item->markedForDeletion = true;
			}
		}

		UpdateSpawnEntity(deltaTime);

	}

	cleanupMarkedEntities();
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	UIManager::getInstance().render();

	paralaxManager->render(renderer);

	if (currentState == GameState::Playing || currentState == GameState::Paused) {
		Vaisseau* player = (Vaisseau*)getEntitieByTag("Player");

		UIManager::getInstance().renderText("Money :", windowWidth / 100, windowHeight / 10, { 255, 255, 255, 255 }, windowWidth / 50);
		UIManager::getInstance().renderNum(playerMoney, Vector2D(windowWidth / 100 + 7 * windowWidth / 80, windowWidth / 17), windowWidth / 37.5f);


		if (player != nullptr)
			UIManager::getInstance().renderHP(player->getHp(), player->getMaxHp(), windowWidth, windowHeight);
	}


	for (auto& entity : entities) {
		if (!entity->markedForDeletion) {
			entity->render(renderer);
		}
	}

	UIManager::getInstance().renderLastMenu();

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	for (auto& entity : entities) {
		delete entity;
	}
	entities.clear();


	UIManager::getInstance().cleanup();

	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}

Entity* Game::getEntitieByTag(std::string t)
{
	for (auto& entity : entities) {
		if (entity->tag == t)
			return entity;
	}
	return nullptr;
}

std::vector<Entity*> Game::getEntitiesByLayer(std::string l)
{
	std::vector<Entity*> result;

	for (auto& entity : entities) {
		if (entity->layer == l)
			result.push_back(entity);
	}
	return result;
}

void Game::addEntity(Entity* entity)
{
	entitiesToAdd.push_back(entity);
}

void Game::cleanupMarkedEntities()
{
	for (auto it = entities.begin(); it != entities.end();) {
		if ((*it)->markedForDeletion) {
			delete* it;
			it = entities.erase(it);
		}
		else {
			++it;
		}
	}
}

int Game::getRandomInt(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void Game::setPLayerMultiplicator(float mult)
{
	Entity* entity = getEntitieByTag("Player");

	if (entity == nullptr)
		return;

	((SpaceShip*)(entity))->damageMultiplier += mult;
}

float Game::getDeltaTime() {
	Uint32 currentTime = SDL_GetTicks();
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;
	return deltaTime;
}

void Game::quit()
{
	isRunning = false;
}

