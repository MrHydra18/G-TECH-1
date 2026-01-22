#include "Mine.h"
#include "Game.h"
#include "AudioManager.h"
#include "Vaisseau.h"

Mine::Mine(Vector2D pos, int dmg, float expRadius, float life, std::function<void(Entity*)> OCE)
    : Entity("Mine"), damage(dmg), explosionRadius(expRadius), maxLifetime(life), onCreateEntity(OCE)
{
    texture = AssetsManager::getInstance().GetTexture("Space/Mine.png");
    m_rect = { (int)pos.x, (int)pos.y, 32, 32 };
    lifetime = 0.0f;
    animTimer = 0.0f;
    currentFrame = 0;
    exploded = false;
    explosionTimer = 0.0f;
    explosionDuration = 0.2f;
    currentExplosionRadius = explosionRadius;
    setLayer("mine");
}

Mine::~Mine()
{
    AssetsManager::getInstance().onTextureDelete("Space/Mine.png");
}

void Mine::render(SDL_Renderer* renderer)
{ 
    if (!exploded) {
       
        SDL_Rect sourceRect = { currentFrame * 48 + 16, 48, 32, 32 };
        SDL_RenderCopy(renderer, texture, &sourceRect, &m_rect);
    }
    else {

        float progress = explosionTimer / explosionDuration;
        int currentRadius = (int)(currentExplosionRadius * progress);

        SDL_SetRenderDrawColor(renderer, 255, 100, 0, 200);
        for (int w = 0; w < currentRadius * 2; w++) {
            for (int h = 0; h < currentRadius * 2; h++) {
                int dx = currentRadius - w;
                int dy = currentRadius - h;
                if ((dx * dx + dy * dy) <= (currentRadius * currentRadius)) {
                    SDL_RenderDrawPoint(renderer, m_rect.x + m_rect.w / 2 + dx, m_rect.y + m_rect.h / 2 + dy);
                }
            }
        }
    }
}

void Mine::update(float deltaTime)
{
    if (exploded) {
        explosionTimer += deltaTime;
        if (explosionTimer >= explosionDuration) {
            markedForDeletion = true;
        }
        return;
    }

    animTimer += deltaTime;
    if (animTimer >= 0.2f) { 
        animTimer = 0.0f;
        currentFrame = (currentFrame + 1) % 4; 
    }


    lifetime += deltaTime;
    if (lifetime >= maxLifetime) {
        explode();
    }
}

void Mine::explode(bool reducedExplosion)
{
    if (exploded) return;

    exploded = true;
    explosionTimer = 0.0f;

    if (reducedExplosion) {
        currentExplosionRadius = explosionRadius / 2.0f;
    }
    else {
        currentExplosionRadius = explosionRadius;
    }

    Game* game = Game::getInstance();
    Entity* player = game->getEntitieByTag("Player");

    if (player && !player->markedForDeletion) {
        Vector2D explosionPos((float)m_rect.x + m_rect.w / 2, (float)m_rect.y + m_rect.h / 2);
        Vector2D playerPos((float)player->m_rect.x + player->m_rect.w / 2,
                          (float)player->m_rect.y + player->m_rect.h / 2);

        Vector2D toPlayer = { playerPos.x - explosionPos.x, playerPos.y - explosionPos.y };
        float distance = sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);


        if (distance <= currentExplosionRadius) {
            ((Vaisseau*)player)->Damage((float)damage);
        }
    }

    AudioManager::getInstance().playSound("Boom");
}
