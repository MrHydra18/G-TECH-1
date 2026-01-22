#pragma once
#include "Entity.h"
#include "AssetsManager.h"
#include <functional>

class Mine : public Entity {
private:
    SDL_Texture* texture;
    float lifetime;
    float maxLifetime;
    float animTimer;
    int currentFrame;
    int damage;
    float explosionRadius;
    float currentExplosionRadius;
    bool exploded;
    float explosionTimer;
    float explosionDuration;
    std::function<void(Entity*)> onCreateEntity;

public:
    Mine(Vector2D pos, int dmg, float expRadius, float life, std::function<void(Entity*)> OCE);
    ~Mine();
    void render(SDL_Renderer* renderer) override;
    void update(float deltaTime) override;
    void explode(bool reducedExplosion = false);
    bool hasExploded() const { return exploded; }
    float getExplosionRadius() const { return explosionRadius; }
    int getDamage() const { return damage; }
};
