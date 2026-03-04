#include "Alan.h"

Alan::Alan(Vector2D pos, Vector2D dir, float speed, int hp, int maxHp, int width, int height, float bd, std::function<void(Entity*)> OCE)
    : Enemy(pos, dir, speed, hp, maxHp, width, height, bd, OCE)
{
    texture = AssetsManager::getInstance().GetTexture("PixelPack/Enemies/Alan.png");

    numImages = 6;
    currentFrame = 0;
    timeBetweenFrames = 0.1f;
    frameTimer = 0.0f;
    lastFrameTime = SDL_GetTicks();
}

Alan::~Alan()
{
    AssetsManager::getInstance().onTextureDelete("PixelPack/Enemies/Alan.png");
}

void Alan::render(SDL_Renderer* renderer)
{
    SDL_Rect sourceRect = { currentFrame * 16, 0, 16, 16 };
    SDL_RenderCopy(renderer, texture, &sourceRect, &m_rect);
}

void Alan::update(float deltaTime) {
    frameTimer += deltaTime;

    if (frameTimer >= timeBetweenFrames)
    {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % numImages;
    }
    Enemy::update(deltaTime);
}