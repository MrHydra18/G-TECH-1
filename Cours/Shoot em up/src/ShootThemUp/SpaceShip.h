#pragma once
#include "Entity.h"
#include "SDL.h"
#include "BasicBullet.h"
#include "GuidedMissile.h"
#include "ExplosiveMissile.h"
#include "LaserBeam.h"
#include "AssetsManager.h"
#include <functional>
#include "AudioManager.h"


class SpaceShip : public Entity
{
protected:
    int hp;
    int maxhp;
    float speed;
    float bulletDelay;
    Uint32 lastShoot = 0;
    Uint32 lastMissile = 0;
    Uint32 lastExplosiveMissile = 0;
    float missileDelay = 500.f; 
    float explosiveMissileDelay = 1000.f; 
    std::function<void(Entity*)> onCreateEntity;
    float scaleRatioX = 1.0f;
    float scaleRatioY = 1.0f;
    float accumulatedDamage = 0.0f;

public:


    SpaceShip(std::string t, Vector2D pos, Vector2D dir, float s, int HP, int maxHp, std::function<void(Entity*)> OCE, float bd, int width, int height) :
        Entity(t), speed(s), hp(HP), maxhp(maxHp), onCreateEntity(OCE), bulletDelay(bd)
    {
        m_rect = { (int)pos.x, (int)pos.y, width, height};
        direction = dir;
    }

    float damageMultiplier = 1.0f;
    void shoot(Vector2D dir, Vector2D pos, int damage, float speed);
    void shootMissile(Vector2D dir, Vector2D pos, int damage, float speed);
    void shootExplosiveMissile(Vector2D dir, Vector2D pos, int damage, float speed, float explosionRadius);
    int getHp() const { return hp; }
    int getMaxHp() const { return maxhp; }
    void Heal(int heal) { hp = hp + heal > maxhp ? maxhp : hp + heal; }
    void Damage(float dmg) {
        accumulatedDamage += dmg;
        if (accumulatedDamage >= 1.0f) {
            int damageToApply = (int)accumulatedDamage;
            hp -= damageToApply;
            accumulatedDamage -= (float)damageToApply;

            std::cout << "damaged; " << hp << "," << damageToApply << std::endl;
            AudioManager::getInstance().playSound("Degat");

            if (hp <= 0) {
                markedForDeletion = true;
                AudioManager::getInstance().playSound("Dead");
            }
        }
    }
    void setScaleRatios(float ratioX, float ratioY) {
        scaleRatioX = ratioX;
        scaleRatioY = ratioY;
    }

    virtual void replaceEntityAfterWindowResize(int oldWidth, int oldHeight, int newWidth, int newHeight) override {
        Entity::replaceEntityAfterWindowResize(oldWidth, oldHeight, newWidth, newHeight);

        // Scaler la vitesse en fonction du ratio
        float ratioX = (float)newWidth / oldWidth;
        speed = speed * ratioX;

        // Mettre à jour les scaleRatios aussi
        scaleRatioX = (float)newWidth / 1600.f;  // Fenêtre de base 1600x900
        scaleRatioY = (float)newHeight / 900.f;
    }

    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void update(float deltaTime) = 0;
};
