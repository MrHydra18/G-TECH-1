#include "SpaceShip.h"
#include "AudioManager.h"

void SpaceShip::shoot(Vector2D dir,Vector2D pos, int damage, float speed)
{

	if (SDL_GetTicks() - lastShoot < bulletDelay)
		return;

	AudioManager::getInstance().playSound("Shoot");
	lastShoot = SDL_GetTicks();

	int scaledWidth = (int)(16 * scaleRatioX);
	int scaledHeight = (int)(16 * scaleRatioY);
	float scaledSpeed = speed * scaleRatioX;

	int finalDamage = (int)(damage * damageMultiplier);

	BasicBullet* bullet = new BasicBullet("bullet", dir,pos, finalDamage, scaledSpeed, scaledWidth,scaledHeight);
	bullet->setLayer("bullet");
	onCreateEntity(bullet);
}

void SpaceShip::shootMissile(Vector2D dir, Vector2D pos, int damage, float speed)
{
	if (SDL_GetTicks() - lastMissile < missileDelay)
		return;

	AudioManager::getInstance().playSound("Shoot");
	lastMissile = SDL_GetTicks();

	int scaledWidth = (int)(16 * scaleRatioX);
	int scaledHeight = (int)(16 * scaleRatioY);
	float scaledSpeed = speed * scaleRatioX;

	int finalDamage = (int)(damage * damageMultiplier);

	GuidedMissile* missile = new GuidedMissile("bullet", dir, pos, finalDamage, scaledSpeed, scaledWidth, scaledHeight);
	missile->setLayer("bullet");
	onCreateEntity(missile);
}

void SpaceShip::shootExplosiveMissile(Vector2D dir, Vector2D pos, int damage, float speed, float explosionRadius)
{
	if (SDL_GetTicks() - lastExplosiveMissile < explosiveMissileDelay)
		return;

	AudioManager::getInstance().playSound("Shoot");
	lastExplosiveMissile = SDL_GetTicks();

	int scaledWidth = (int)(16 * scaleRatioX);
	int scaledHeight = (int)(16 * scaleRatioY);
	float scaledSpeed = speed * scaleRatioX;
	float scaledRadius = explosionRadius * scaleRatioX;

	int finalDamage = (int)(damage * damageMultiplier);

	ExplosiveMissile* missile = new ExplosiveMissile("bullet", dir, pos, finalDamage, scaledSpeed, scaledRadius, scaledWidth, scaledHeight);
	missile->setLayer("bullet");
	onCreateEntity(missile);
}
